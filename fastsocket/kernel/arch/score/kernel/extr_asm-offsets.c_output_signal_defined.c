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
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGIOT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPROF ; 
 int /*<<< orphan*/  SIGPWR ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGSYS ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIGURG ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  _SIGABRT ; 
 int /*<<< orphan*/  _SIGALRM ; 
 int /*<<< orphan*/  _SIGBUS ; 
 int /*<<< orphan*/  _SIGCHLD ; 
 int /*<<< orphan*/  _SIGCONT ; 
 int /*<<< orphan*/  _SIGFPE ; 
 int /*<<< orphan*/  _SIGHUP ; 
 int /*<<< orphan*/  _SIGILL ; 
 int /*<<< orphan*/  _SIGINT ; 
 int /*<<< orphan*/  _SIGIO ; 
 int /*<<< orphan*/  _SIGIOT ; 
 int /*<<< orphan*/  _SIGKILL ; 
 int /*<<< orphan*/  _SIGPIPE ; 
 int /*<<< orphan*/  _SIGPROF ; 
 int /*<<< orphan*/  _SIGPWR ; 
 int /*<<< orphan*/  _SIGQUIT ; 
 int /*<<< orphan*/  _SIGSEGV ; 
 int /*<<< orphan*/  _SIGSTOP ; 
 int /*<<< orphan*/  _SIGSYS ; 
 int /*<<< orphan*/  _SIGTERM ; 
 int /*<<< orphan*/  _SIGTRAP ; 
 int /*<<< orphan*/  _SIGTSTP ; 
 int /*<<< orphan*/  _SIGTTIN ; 
 int /*<<< orphan*/  _SIGTTOU ; 
 int /*<<< orphan*/  _SIGURG ; 
 int /*<<< orphan*/  _SIGUSR1 ; 
 int /*<<< orphan*/  _SIGUSR2 ; 
 int /*<<< orphan*/  _SIGVTALRM ; 
 int /*<<< orphan*/  _SIGWINCH ; 
 int /*<<< orphan*/  _SIGXCPU ; 
 int /*<<< orphan*/  _SIGXFSZ ; 

void output_signal_defined(void)
{
	COMMENT("Linux signal numbers.");
	DEFINE(_SIGHUP, SIGHUP);
	DEFINE(_SIGINT, SIGINT);
	DEFINE(_SIGQUIT, SIGQUIT);
	DEFINE(_SIGILL, SIGILL);
	DEFINE(_SIGTRAP, SIGTRAP);
	DEFINE(_SIGIOT, SIGIOT);
	DEFINE(_SIGABRT, SIGABRT);
	DEFINE(_SIGFPE, SIGFPE);
	DEFINE(_SIGKILL, SIGKILL);
	DEFINE(_SIGBUS, SIGBUS);
	DEFINE(_SIGSEGV, SIGSEGV);
	DEFINE(_SIGSYS, SIGSYS);
	DEFINE(_SIGPIPE, SIGPIPE);
	DEFINE(_SIGALRM, SIGALRM);
	DEFINE(_SIGTERM, SIGTERM);
	DEFINE(_SIGUSR1, SIGUSR1);
	DEFINE(_SIGUSR2, SIGUSR2);
	DEFINE(_SIGCHLD, SIGCHLD);
	DEFINE(_SIGPWR, SIGPWR);
	DEFINE(_SIGWINCH, SIGWINCH);
	DEFINE(_SIGURG, SIGURG);
	DEFINE(_SIGIO, SIGIO);
	DEFINE(_SIGSTOP, SIGSTOP);
	DEFINE(_SIGTSTP, SIGTSTP);
	DEFINE(_SIGCONT, SIGCONT);
	DEFINE(_SIGTTIN, SIGTTIN);
	DEFINE(_SIGTTOU, SIGTTOU);
	DEFINE(_SIGVTALRM, SIGVTALRM);
	DEFINE(_SIGPROF, SIGPROF);
	DEFINE(_SIGXCPU, SIGXCPU);
	DEFINE(_SIGXFSZ, SIGXFSZ);
	BLANK();
}