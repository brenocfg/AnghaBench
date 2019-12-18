#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verdef ;
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  opath ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  off64_t ;
typedef  int /*<<< orphan*/  ipath ;
struct TYPE_4__ {int dt_cpp_argc; int dt_vmax; int dt_stdcmode; int /*<<< orphan*/  dt_cpp_path; int /*<<< orphan*/  dt_cpp_argv; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  act ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DT_STDC_XA 130 
#define  DT_STDC_XC 129 
#define  DT_STDC_XT 128 
 scalar_t__ EDT_CPPENT ; 
 scalar_t__ EDT_CPPERR ; 
 scalar_t__ EDT_CPPEXEC ; 
 scalar_t__ EDT_CPPFORK ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOENT ; 
 int EOF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt_set_errno (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int fork1 () ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftello64 (int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * tmpfile () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *
dt_preproc(dtrace_hdl_t *dtp, FILE *ifp)
{
	int argc = dtp->dt_cpp_argc;
	char **argv = malloc(sizeof (char *) * (argc + 5));
	FILE *ofp = tmpfile();

#ifdef illumos
	char ipath[20], opath[20]; /* big enough for /dev/fd/ + INT_MAX + \0 */
#endif
	char verdef[32]; /* big enough for -D__SUNW_D_VERSION=0x%08x + \0 */

	struct sigaction act, oact;
	sigset_t mask, omask;

	int wstat, estat;
	pid_t pid;
#ifdef illumos
	off64_t off;
#else
	off_t off = 0;
#endif
	int c;

	if (argv == NULL || ofp == NULL) {
		(void) dt_set_errno(dtp, errno);
		goto err;
	}

	/*
	 * If the input is a seekable file, see if it is an interpreter file.
	 * If we see #!, seek past the first line because cpp will choke on it.
	 * We start cpp just prior to the \n at the end of this line so that
	 * it still sees the newline, ensuring that #line values are correct.
	 */
	if (isatty(fileno(ifp)) == 0 && (off = ftello64(ifp)) != -1) {
		if ((c = fgetc(ifp)) == '#' && (c = fgetc(ifp)) == '!') {
			for (off += 2; c != '\n'; off++) {
				if ((c = fgetc(ifp)) == EOF)
					break;
			}
			if (c == '\n')
				off--; /* start cpp just prior to \n */
		}
		(void) fflush(ifp);
		(void) fseeko64(ifp, off, SEEK_SET);
	}

#ifdef illumos
	(void) snprintf(ipath, sizeof (ipath), "/dev/fd/%d", fileno(ifp));
	(void) snprintf(opath, sizeof (opath), "/dev/fd/%d", fileno(ofp));
#endif

	bcopy(dtp->dt_cpp_argv, argv, sizeof (char *) * argc);

	(void) snprintf(verdef, sizeof (verdef),
	    "-D__SUNW_D_VERSION=0x%08x", dtp->dt_vmax);
	argv[argc++] = verdef;

#ifdef illumos
	switch (dtp->dt_stdcmode) {
	case DT_STDC_XA:
	case DT_STDC_XT:
		argv[argc++] = "-D__STDC__=0";
		break;
	case DT_STDC_XC:
		argv[argc++] = "-D__STDC__=1";
		break;
	}

	argv[argc++] = ipath;
	argv[argc++] = opath;
#else
	argv[argc++] = "-P";
#endif
	argv[argc] = NULL;

	/*
	 * libdtrace must be able to be embedded in other programs that may
	 * include application-specific signal handlers.  Therefore, if we
	 * need to fork to run cpp(1), we must avoid generating a SIGCHLD
	 * that could confuse the containing application.  To do this,
	 * we block SIGCHLD and reset its disposition to SIG_DFL.
	 * We restore our signal state once we are done.
	 */
	(void) sigemptyset(&mask);
	(void) sigaddset(&mask, SIGCHLD);
	(void) sigprocmask(SIG_BLOCK, &mask, &omask);

	bzero(&act, sizeof (act));
	act.sa_handler = SIG_DFL;
	(void) sigaction(SIGCHLD, &act, &oact);

	if ((pid = fork1()) == -1) {
		(void) sigaction(SIGCHLD, &oact, NULL);
		(void) sigprocmask(SIG_SETMASK, &omask, NULL);
		(void) dt_set_errno(dtp, EDT_CPPFORK);
		goto err;
	}

	if (pid == 0) {
#ifndef illumos
		if (isatty(fileno(ifp)) == 0)
			lseek(fileno(ifp), off, SEEK_SET);
		dup2(fileno(ifp), 0);
		dup2(fileno(ofp), 1);
#endif
		(void) execvp(dtp->dt_cpp_path, argv);
		_exit(errno == ENOENT ? 127 : 126);
	}

	do {
		dt_dprintf("waiting for %s (PID %d)\n", dtp->dt_cpp_path,
		    (int)pid);
	} while (waitpid(pid, &wstat, 0) == -1 && errno == EINTR);

	(void) sigaction(SIGCHLD, &oact, NULL);
	(void) sigprocmask(SIG_SETMASK, &omask, NULL);

	dt_dprintf("%s returned exit status 0x%x\n", dtp->dt_cpp_path, wstat);
	estat = WIFEXITED(wstat) ? WEXITSTATUS(wstat) : -1;

	if (estat != 0) {
		switch (estat) {
		case 126:
			(void) dt_set_errno(dtp, EDT_CPPEXEC);
			break;
		case 127:
			(void) dt_set_errno(dtp, EDT_CPPENT);
			break;
		default:
			(void) dt_set_errno(dtp, EDT_CPPERR);
		}
		goto err;
	}

	free(argv);
	(void) fflush(ofp);
	(void) fseek(ofp, 0, SEEK_SET);
	return (ofp);

err:
	free(argv);
	(void) fclose(ofp);
	return (NULL);
}