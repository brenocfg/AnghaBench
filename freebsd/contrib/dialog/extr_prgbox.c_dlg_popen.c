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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 char** dlg_string_to_argv (char*) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int fork () ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

FILE *
dlg_popen(const char *command, const char *type)
{
    FILE *result = 0;
    int fd[2];
    char *blob;
    char **argv;

    if ((*type == 'r' || *type != 'w') && pipe(fd) == 0) {
	switch (fork()) {
	case -1:		/* Error. */
	    (void) close(fd[0]);
	    (void) close(fd[1]);
	    break;
	case 0:		/* child. */
	    if (*type == 'r') {
		if (fd[1] != STDOUT_FILENO) {
		    (void) dup2(fd[1], STDOUT_FILENO);
		    (void) close(fd[1]);
		}
		(void) dup2(STDOUT_FILENO, STDERR_FILENO);
		(void) close(fd[0]);
	    } else {
		if (fd[0] != STDIN_FILENO) {
		    (void) dup2(fd[0], STDIN_FILENO);
		    (void) close(fd[0]);
		}
		(void) close(fd[1]);
		(void) close(STDERR_FILENO);
	    }
	    /*
	     * Bourne shell needs "-c" option to force it to use only the
	     * given command.  Also, it needs the command to be parsed into
	     * tokens.
	     */
	    if ((blob = malloc(10 + strlen(command))) != 0) {
		sprintf(blob, "sh -c \"%s\"", command);
		argv = dlg_string_to_argv(blob);
		execvp("sh", argv);
	    }
	    _exit(127);
	    /* NOTREACHED */
	default:		/* parent */
	    if (*type == 'r') {
		result = fdopen(fd[0], type);
		(void) close(fd[1]);
	    } else {
		result = fdopen(fd[1], type);
		(void) close(fd[0]);
	    }
	    break;
	}
    }

    return result;
}