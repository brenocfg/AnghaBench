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
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  IXP2000_T1_CLR ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int) ; 
 scalar_t__* missing_jiffy_timer_csr ; 
 scalar_t__ next_jiffy_time ; 
 long ticks_per_jiffy ; 
 int /*<<< orphan*/  timer_tick () ; 

__attribute__((used)) static int ixp2000_timer_interrupt(int irq, void *dev_id)
{
	/* clear timer 1 */
	ixp2000_reg_wrb(IXP2000_T1_CLR, 1);

	while ((signed long)(next_jiffy_time - *missing_jiffy_timer_csr)
							>= ticks_per_jiffy) {
		timer_tick();
		next_jiffy_time -= ticks_per_jiffy;
	}

	return IRQ_HANDLED;
}