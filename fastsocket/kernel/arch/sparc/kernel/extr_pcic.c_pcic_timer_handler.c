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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  do_timer (int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  pcic_clear_clock_irq () ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtime_lock ; 

__attribute__((used)) static irqreturn_t pcic_timer_handler (int irq, void *h)
{
	write_seqlock(&xtime_lock);	/* Dummy, to show that we remember */
	pcic_clear_clock_irq();
	do_timer(1);
	write_sequnlock(&xtime_lock);
#ifndef CONFIG_SMP
	update_process_times(user_mode(get_irq_regs()));
#endif
	return IRQ_HANDLED;
}