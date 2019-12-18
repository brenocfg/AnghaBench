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
 scalar_t__ next_jiffy_time ; 
 scalar_t__ read_tcr1 () ; 
 long ticks_per_jiffy ; 
 int /*<<< orphan*/  timer_tick () ; 
 int /*<<< orphan*/  write_tisr (int) ; 

__attribute__((used)) static irqreturn_t
iop_timer_interrupt(int irq, void *dev_id)
{
	write_tisr(1);

	while ((signed long)(next_jiffy_time - read_tcr1())
		>= ticks_per_jiffy) {
		timer_tick();
		next_jiffy_time -= ticks_per_jiffy;
	}

	return IRQ_HANDLED;
}