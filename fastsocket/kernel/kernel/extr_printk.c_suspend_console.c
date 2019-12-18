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
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  console_sem ; 
 int /*<<< orphan*/  console_suspend_enabled ; 
 int console_suspended ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void suspend_console(void)
{
	if (!console_suspend_enabled)
		return;
	printk("Suspending console(s) (use no_console_suspend to debug)\n");
	acquire_console_sem();
	console_suspended = 1;
	up(&console_sem);
}