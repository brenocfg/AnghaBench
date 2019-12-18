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

__attribute__((used)) static void
sigchld_handler (int signo)
{
  /* Do nothing.  The only reason for this handler is that it allows
     us to use sigsuspend in lin_lwp_wait above to wait for the
     arrival of a SIGCHLD.  */
}