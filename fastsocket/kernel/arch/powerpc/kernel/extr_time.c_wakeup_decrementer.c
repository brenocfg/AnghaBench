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
 int /*<<< orphan*/  __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_jiffy ; 
 int /*<<< orphan*/  set_dec (unsigned long) ; 
 unsigned long tb_ticks_per_jiffy ; 
 unsigned long tb_ticks_since (int /*<<< orphan*/ ) ; 

void wakeup_decrementer(void)
{
	unsigned long ticks;

	/*
	 * The timebase gets saved on sleep and restored on wakeup,
	 * so all we need to do is to reset the decrementer.
	 */
	ticks = tb_ticks_since(__get_cpu_var(last_jiffy));
	if (ticks < tb_ticks_per_jiffy)
		ticks = tb_ticks_per_jiffy - ticks;
	else
		ticks = 1;
	set_dec(ticks);
}