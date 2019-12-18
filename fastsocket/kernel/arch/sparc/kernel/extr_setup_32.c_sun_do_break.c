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
 int /*<<< orphan*/  flush_user_windows () ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  prom_cmdline () ; 
 int /*<<< orphan*/  stop_a_enabled ; 

void sun_do_break(void)
{
	if (!stop_a_enabled)
		return;

	printk("\n");
	flush_user_windows();

	prom_cmdline();
}