#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_3__ {scalar_t__ ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int SA_ONSTACK ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGSTKSZ ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  segv_handler ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 scalar_t__ sigaltstack (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
darwin_rs6000_extra_signals (void)
{
  struct sigaction sact;
  stack_t sigstk;

  sigstk.ss_sp = xmalloc (SIGSTKSZ);
  sigstk.ss_size = SIGSTKSZ;
  sigstk.ss_flags = 0;
  if (sigaltstack (&sigstk, NULL) < 0)
    fatal_error ("While setting up signal stack: %m");

  sigemptyset(&sact.sa_mask);
  sact.sa_flags = SA_ONSTACK | SA_SIGINFO;
  sact.sa_sigaction = segv_handler;
  if (sigaction (SIGSEGV, &sact, 0) < 0) 
    fatal_error ("While setting up signal handler: %m");
}