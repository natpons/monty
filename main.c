#include "monty.h"
/**
 * main - interpreter de monty
 * @argc: the arguments number
 * @argv: double pointer to the string of arguments
 * Return: EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int main(int argc, char **argv)
{
	stack_t *stack = NULL;
	unsigned int line_number = 0;
	FILE *file;
	char *buffer = NULL;
	size_t bufsize = 0;
	char *delim, *op;

	delim = "\n\t\r ";
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &bufsize, file) != -1)
	{
		line_number++;
		op = strtok(buffer, delim);
		if (op != NULL && op[0] != '#')
		{
			get_operation(op, &stack, line_number);
		}
	}
	on_exit(free_buffer, &buffer);
	on_exit(free_stack, &stack);
	on_exit(file_close, file);
	exit(EXIT_SUCCESS);
}
