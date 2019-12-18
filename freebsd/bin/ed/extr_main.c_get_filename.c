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
 int PATH_MAX ; 
 int /*<<< orphan*/  REALLOC (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SKIP_BLANKS () ; 
 char* errmsg ; 
 char* get_extended_line (int*,int) ; 
 int get_shell_command () ; 
 char* ibufp ; 
 scalar_t__ is_legal_filename (char*) ; 
 char* old_filename ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* shcmd ; 

char *
get_filename(void)
{
	static char *file = NULL;
	static int filesz = 0;

	int n;

	if (*ibufp != '\n') {
		SKIP_BLANKS();
		if (*ibufp == '\n') {
			errmsg = "invalid filename";
			return NULL;
		} else if ((ibufp = get_extended_line(&n, 1)) == NULL)
			return NULL;
		else if (*ibufp == '!') {
			ibufp++;
			if ((n = get_shell_command()) < 0)
				return NULL;
			if (n)
				printf("%s\n", shcmd + 1);
			return shcmd;
		} else if (n > PATH_MAX - 1) {
			errmsg = "filename too long";
			return  NULL;
		}
	}
#ifndef BACKWARDS
	else if (*old_filename == '\0') {
		errmsg = "no current filename";
		return  NULL;
	}
#endif
	REALLOC(file, filesz, PATH_MAX, NULL);
	for (n = 0; *ibufp != '\n';)
		file[n++] = *ibufp++;
	file[n] = '\0';
	return is_legal_filename(file) ? file : NULL;
}