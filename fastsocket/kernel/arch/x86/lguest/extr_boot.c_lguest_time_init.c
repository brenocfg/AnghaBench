#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  clockevents_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  clocksource_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_lguest_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lguest_clock ; 
 TYPE_1__ lguest_clockevent ; 
 int /*<<< orphan*/  lguest_time_irq ; 
 int /*<<< orphan*/  set_irq_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_time_init(void)
{
	/* Set up the timer interrupt (0) to go to our simple timer routine */
	set_irq_handler(0, lguest_time_irq);

	clocksource_register(&lguest_clock);

	/* We can't set cpumask in the initializer: damn C limitations!  Set it
	 * here and register our timer device. */
	lguest_clockevent.cpumask = cpumask_of(0);
	clockevents_register_device(&lguest_clockevent);

	/* Finally, we unblock the timer interrupt. */
	enable_lguest_irq(0);
}