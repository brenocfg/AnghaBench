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
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  WAIT_T ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int,char*) ; 
 char* Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Buf_Size (int /*<<< orphan*/ *) ; 
 int EINTR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JobReapChild (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Shell_Init () ; 
 int /*<<< orphan*/  UNCONST (char const**) ; 
 int /*<<< orphan*/  Var_ExportVars () ; 
 int /*<<< orphan*/  WEXITSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int) ; 
 char* bmake_malloc (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  execv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 int read (int,char*,int) ; 
 char* shellName ; 
 int /*<<< orphan*/  shellPath ; 
 int vFork () ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
Cmd_Exec(const char *cmd, const char **errnum)
{
    const char	*args[4];   	/* Args for invoking the shell */
    int 	fds[2];	    	/* Pipe streams */
    int 	cpid;	    	/* Child PID */
    int 	pid;	    	/* PID from wait() */
    char	*res;		/* result */
    WAIT_T	status;		/* command exit status */
    Buffer	buf;		/* buffer to store the result */
    char	*cp;
    int		cc;		/* bytes read, or -1 */
    int		savederr;	/* saved errno */


    *errnum = NULL;

    if (!shellName)
	Shell_Init();
    /*
     * Set up arguments for shell
     */
    args[0] = shellName;
    args[1] = "-c";
    args[2] = cmd;
    args[3] = NULL;

    /*
     * Open a pipe for fetching its output
     */
    if (pipe(fds) == -1) {
	*errnum = "Couldn't create pipe for \"%s\"";
	goto bad;
    }

    /*
     * Fork
     */
    switch (cpid = vFork()) {
    case 0:
	/*
	 * Close input side of pipe
	 */
	(void)close(fds[0]);

	/*
	 * Duplicate the output stream to the shell's output, then
	 * shut the extra thing down. Note we don't fetch the error
	 * stream...why not? Why?
	 */
	(void)dup2(fds[1], 1);
	(void)close(fds[1]);

	Var_ExportVars();

	(void)execv(shellPath, UNCONST(args));
	_exit(1);
	/*NOTREACHED*/

    case -1:
	*errnum = "Couldn't exec \"%s\"";
	goto bad;

    default:
	/*
	 * No need for the writing half
	 */
	(void)close(fds[1]);

	savederr = 0;
	Buf_Init(&buf, 0);

	do {
	    char   result[BUFSIZ];
	    cc = read(fds[0], result, sizeof(result));
	    if (cc > 0)
		Buf_AddBytes(&buf, cc, result);
	}
	while (cc > 0 || (cc == -1 && errno == EINTR));
	if (cc == -1)
	    savederr = errno;

	/*
	 * Close the input side of the pipe.
	 */
	(void)close(fds[0]);

	/*
	 * Wait for the process to exit.
	 */
	while(((pid = waitpid(cpid, &status, 0)) != cpid) && (pid >= 0)) {
	    JobReapChild(pid, status, FALSE);
	    continue;
	}
	cc = Buf_Size(&buf);
	res = Buf_Destroy(&buf, FALSE);

	if (savederr != 0)
	    *errnum = "Couldn't read shell's output for \"%s\"";

	if (WIFSIGNALED(status))
	    *errnum = "\"%s\" exited on a signal";
	else if (WEXITSTATUS(status) != 0)
	    *errnum = "\"%s\" returned non-zero status";

	/*
	 * Null-terminate the result, convert newlines to spaces and
	 * install it in the variable.
	 */
	res[cc] = '\0';
	cp = &res[cc];

	if (cc > 0 && *--cp == '\n') {
	    /*
	     * A final newline is just stripped
	     */
	    *cp-- = '\0';
	}
	while (cp >= res) {
	    if (*cp == '\n') {
		*cp = ' ';
	    }
	    cp--;
	}
	break;
    }
    return res;
bad:
    res = bmake_malloc(1);
    *res = '\0';
    return res;
}