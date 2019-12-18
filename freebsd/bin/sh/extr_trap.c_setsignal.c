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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; scalar_t__ sa_handler; } ;
typedef  scalar_t__ sig_t ;

/* Variables and functions */
#define  SIGINT 135 
#define  SIGQUIT 134 
#define  SIGTERM 133 
#define  SIGTSTP 132 
 int SIGTTIN ; 
#define  SIGTTOU 131 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
#define  S_CATCH 130 
#define  S_DFL 129 
 char S_HARD_IGN ; 
#define  S_IGN 128 
 char S_RESET ; 
 int /*<<< orphan*/  getsigaction (int,scalar_t__*) ; 
 int /*<<< orphan*/  iflag ; 
 scalar_t__ mflag ; 
 scalar_t__ onsig ; 
 int /*<<< orphan*/  rootshell ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 char* sigmode ; 
 char** trap ; 

void
setsignal(int signo)
{
	int action;
	sig_t sigact = SIG_DFL;
	struct sigaction sa;
	char *t;

	if ((t = trap[signo]) == NULL)
		action = S_DFL;
	else if (*t != '\0')
		action = S_CATCH;
	else
		action = S_IGN;
	if (action == S_DFL) {
		switch (signo) {
		case SIGINT:
			action = S_CATCH;
			break;
		case SIGQUIT:
#ifdef DEBUG
			{
			extern int debug;

			if (debug)
				break;
			}
#endif
			action = S_CATCH;
			break;
		case SIGTERM:
			if (rootshell && iflag)
				action = S_IGN;
			break;
#if JOBS
		case SIGTSTP:
		case SIGTTOU:
			if (rootshell && mflag)
				action = S_IGN;
			break;
#endif
		}
	}

	t = &sigmode[signo];
	if (*t == 0) {
		/*
		 * current setting unknown
		 */
		if (!getsigaction(signo, &sigact)) {
			/*
			 * Pretend it worked; maybe we should give a warning
			 * here, but other shells don't. We don't alter
			 * sigmode, so that we retry every time.
			 */
			return;
		}
		if (sigact == SIG_IGN) {
			if (mflag && (signo == SIGTSTP ||
			     signo == SIGTTIN || signo == SIGTTOU)) {
				*t = S_IGN;	/* don't hard ignore these */
			} else
				*t = S_HARD_IGN;
		} else {
			*t = S_RESET;	/* force to be set */
		}
	}
	if (*t == S_HARD_IGN || *t == action)
		return;
	switch (action) {
		case S_DFL:	sigact = SIG_DFL;	break;
		case S_CATCH:  	sigact = onsig;		break;
		case S_IGN:	sigact = SIG_IGN;	break;
	}
	*t = action;
	sa.sa_handler = sigact;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signo, &sa, NULL);
}