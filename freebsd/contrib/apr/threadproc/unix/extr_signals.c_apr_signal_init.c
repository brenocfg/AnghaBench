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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_NUMSIG ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGCLD ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGEMT ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGIOT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPOLL ; 
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
 int /*<<< orphan*/ * apr_psprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ ** signal_description ; 
 int /*<<< orphan*/  store_desc (int /*<<< orphan*/ ,char*) ; 

void apr_signal_init(apr_pool_t *pglobal)
{
    int sig;

    store_desc(0, "Signal 0");

#ifdef SIGHUP
    store_desc(SIGHUP, "Hangup");
#endif
#ifdef SIGINT
    store_desc(SIGINT, "Interrupt");
#endif
#ifdef SIGQUIT
    store_desc(SIGQUIT, "Quit");
#endif
#ifdef SIGILL
    store_desc(SIGILL, "Illegal instruction");
#endif
#ifdef SIGTRAP
    store_desc(SIGTRAP, "Trace/BPT trap");
#endif
#ifdef SIGIOT
    store_desc(SIGIOT, "IOT instruction");
#endif
#ifdef SIGABRT
    store_desc(SIGABRT, "Abort");
#endif
#ifdef SIGEMT
    store_desc(SIGEMT, "Emulator trap");
#endif
#ifdef SIGFPE
    store_desc(SIGFPE, "Arithmetic exception");
#endif
#ifdef SIGKILL
    store_desc(SIGKILL, "Killed");
#endif
#ifdef SIGBUS
    store_desc(SIGBUS, "Bus error");
#endif
#ifdef SIGSEGV
    store_desc(SIGSEGV, "Segmentation fault");
#endif
#ifdef SIGSYS
    store_desc(SIGSYS, "Bad system call");
#endif
#ifdef SIGPIPE
    store_desc(SIGPIPE, "Broken pipe");
#endif
#ifdef SIGALRM
    store_desc(SIGALRM, "Alarm clock");
#endif
#ifdef SIGTERM
    store_desc(SIGTERM, "Terminated");
#endif
#ifdef SIGUSR1
    store_desc(SIGUSR1, "User defined signal 1");
#endif
#ifdef SIGUSR2
    store_desc(SIGUSR2, "User defined signal 2");
#endif
#ifdef SIGCLD
    store_desc(SIGCLD, "Child status change");
#endif
#ifdef SIGCHLD
    store_desc(SIGCHLD, "Child status change");
#endif
#ifdef SIGPWR
    store_desc(SIGPWR, "Power-fail restart");
#endif
#ifdef SIGWINCH
    store_desc(SIGWINCH, "Window changed");
#endif
#ifdef SIGURG
    store_desc(SIGURG, "urgent socket condition");
#endif
#ifdef SIGPOLL
    store_desc(SIGPOLL, "Pollable event occurred");
#endif
#ifdef SIGIO
    store_desc(SIGIO, "socket I/O possible");
#endif
#ifdef SIGSTOP
    store_desc(SIGSTOP, "Stopped (signal)");
#endif
#ifdef SIGTSTP
    store_desc(SIGTSTP, "Stopped");
#endif
#ifdef SIGCONT
    store_desc(SIGCONT, "Continued");
#endif
#ifdef SIGTTIN
    store_desc(SIGTTIN, "Stopped (tty input)");
#endif
#ifdef SIGTTOU
    store_desc(SIGTTOU, "Stopped (tty output)");
#endif
#ifdef SIGVTALRM
    store_desc(SIGVTALRM, "virtual timer expired");
#endif
#ifdef SIGPROF
    store_desc(SIGPROF, "profiling timer expired");
#endif
#ifdef SIGXCPU
    store_desc(SIGXCPU, "exceeded cpu limit");
#endif
#ifdef SIGXFSZ
    store_desc(SIGXFSZ, "exceeded file size limit");
#endif

    for (sig = 0; sig < APR_NUMSIG; ++sig)
        if (signal_description[sig] == NULL)
            signal_description[sig] = apr_psprintf(pglobal, "signal #%d", sig);
}