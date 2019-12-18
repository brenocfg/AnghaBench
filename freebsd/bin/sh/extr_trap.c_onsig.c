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
 int /*<<< orphan*/  SET_PENDING_INT ; 
 int SIGCHLD ; 
 int SIGINT ; 
 int SIGQUIT ; 
 int* gotsig ; 
 int /*<<< orphan*/  ignore_sigchld ; 
 int /*<<< orphan*/  in_dotrap ; 
 int /*<<< orphan*/  onint () ; 
 int pendingsig ; 
 int pendingsig_waitcmd ; 
 scalar_t__ suppressint ; 
 char** trap ; 

void
onsig(int signo)
{

	if (signo == SIGINT && trap[SIGINT] == NULL) {
		/*
		 * The !in_dotrap here is safe.  The only way we can arrive
		 * here with in_dotrap set is that a trap handler set SIGINT to
		 * SIG_DFL and killed itself.
		 */
		if (suppressint && !in_dotrap)
			SET_PENDING_INT;
		else
			onint();
		return;
	}

	/* If we are currently in a wait builtin, prepare to break it */
	if (signo == SIGINT || signo == SIGQUIT)
		pendingsig_waitcmd = signo;

	if (trap[signo] != NULL && trap[signo][0] != '\0' &&
	    (signo != SIGCHLD || !ignore_sigchld)) {
		gotsig[signo] = 1;
		pendingsig = signo;
		pendingsig_waitcmd = signo;
	}
}