#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDSKBMODE ; 
 int /*<<< orphan*/  K_MEDIUMRAW ; 
 int SA_RESETHAND ; 
 int SA_RESTART ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_terminal_flush () ; 
 int /*<<< orphan*/  linux_terminal_init () ; 
 int /*<<< orphan*/  linux_terminal_restore_input ; 
 int /*<<< orphan*/  linux_terminal_restore_signal ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

bool linux_terminal_disable_input(void)
{
   struct sigaction sa = {{0}};

   /* Avoid accidentally typing stuff. */
   if (!isatty(0))
      return false;

   if (!linux_terminal_init())
      return false;

   if (ioctl(0, KDSKBMODE, K_MEDIUMRAW) < 0)
   {
      linux_terminal_flush();
      return false;
   }

   sa.sa_handler = linux_terminal_restore_signal;
   sa.sa_flags   = SA_RESTART | SA_RESETHAND;
   sigemptyset(&sa.sa_mask);

   /* Trap some standard termination codes so we
    * can restore the keyboard before we lose control. */
   sigaction(SIGABRT, &sa, NULL);
   sigaction(SIGBUS,  &sa, NULL);
   sigaction(SIGFPE,  &sa, NULL);
   sigaction(SIGILL,  &sa, NULL);
   sigaction(SIGQUIT, &sa, NULL);
   sigaction(SIGSEGV, &sa, NULL);

   atexit(linux_terminal_restore_input);

   return true;
}