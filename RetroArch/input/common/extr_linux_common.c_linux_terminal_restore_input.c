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
 int /*<<< orphan*/  KDSKBMODE ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int linux_stdin_claimed ; 
 int /*<<< orphan*/  linux_terminal_flush () ; 
 int oldKbmd ; 

void linux_terminal_restore_input(void)
{
   if (oldKbmd == 0xffff)
      return;

   if (ioctl(0, KDSKBMODE, oldKbmd) < 0)
      return;

   linux_terminal_flush();
   oldKbmd = 0xffff;

   linux_stdin_claimed = false;
}