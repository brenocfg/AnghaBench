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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
struct rlimit {void* rlim_max; void* rlim_cur; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 void* RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
dt_coredump(void)
{
	const char msg[] = "libdtrace DEBUG: [ forcing coredump ]\n";

	struct sigaction act;
	struct rlimit lim;

	(void) write(STDERR_FILENO, msg, sizeof (msg) - 1);

	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;

	(void) sigemptyset(&act.sa_mask);
	(void) sigaction(SIGABRT, &act, NULL);

	lim.rlim_cur = RLIM_INFINITY;
	lim.rlim_max = RLIM_INFINITY;

	(void) setrlimit(RLIMIT_CORE, &lim);
	abort();
}