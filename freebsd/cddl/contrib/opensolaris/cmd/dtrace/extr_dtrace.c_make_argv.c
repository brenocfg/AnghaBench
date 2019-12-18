#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char** malloc (int) ; 
 int strlen (char*) ; 
 char* strtok (char*,char const*) ; 

__attribute__((used)) static char **
make_argv(char *s)
{
	const char *ws = "\f\n\r\t\v ";
	char **argv = malloc(sizeof (char *) * (strlen(s) / 2 + 1));
	int argc = 0;
	char *p = s;

	if (argv == NULL)
		return (NULL);

	for (p = strtok(s, ws); p != NULL; p = strtok(NULL, ws))
		argv[argc++] = p;

	if (argc == 0)
		argv[argc++] = s;

	argv[argc] = NULL;
	return (argv);
}