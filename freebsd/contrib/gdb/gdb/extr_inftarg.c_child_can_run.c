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
 int /*<<< orphan*/  child_suppress_run ; 

__attribute__((used)) static int
child_can_run (void)
{
  /* This variable is controlled by modules that sit atop inftarg that may layer
     their own process structure atop that provided here.  hpux-thread.c does
     this because of the Hpux user-mode level thread model.  */

  return !child_suppress_run;
}