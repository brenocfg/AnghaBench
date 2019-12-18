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
struct jmploc {int /*<<< orphan*/  loc; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEINTON ; 
 int SIGSTOP ; 
 int SIGTSTP ; 
 int SIGTTIN ; 
 int SIGTTOU ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ evalskip ; 
 int /*<<< orphan*/  evalstring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exiting ; 
 int exiting_exitstatus ; 
 int exitstatus ; 
 int /*<<< orphan*/  flushall () ; 
 int /*<<< orphan*/  getpid () ; 
 struct jmploc* handler ; 
 scalar_t__ in_dotrap ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int last_trapsig ; 
 int oexitstatus ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setjobctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** trap ; 

void
exitshell_savedstatus(void)
{
	struct jmploc loc1, loc2;
	char *p;
	int sig = 0;
	sigset_t sigs;

	if (!exiting) {
		if (in_dotrap && last_trapsig) {
			sig = last_trapsig;
			exiting_exitstatus = sig + 128;
		} else
			exiting_exitstatus = oexitstatus;
	}
	exitstatus = oexitstatus = exiting_exitstatus;
	if (!setjmp(loc1.loc)) {
		handler = &loc1;
		if ((p = trap[0]) != NULL && *p != '\0') {
			/*
			 * Reset evalskip, or the trap on EXIT could be
			 * interrupted if the last command was a "return".
			 */
			evalskip = 0;
			trap[0] = NULL;
			FORCEINTON;
			evalstring(p, 0);
		}
	}
	if (!setjmp(loc2.loc)) {
		handler = &loc2;		/* probably unnecessary */
		FORCEINTON;
		flushall();
#if JOBS
		setjobctl(0);
#endif
	}
	if (sig != 0 && sig != SIGSTOP && sig != SIGTSTP && sig != SIGTTIN &&
	    sig != SIGTTOU) {
		signal(sig, SIG_DFL);
		sigemptyset(&sigs);
		sigaddset(&sigs, sig);
		sigprocmask(SIG_UNBLOCK, &sigs, NULL);
		kill(getpid(), sig);
		/* If the default action is to ignore, fall back to _exit(). */
	}
	_exit(exiting_exitstatus);
}