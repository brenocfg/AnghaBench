#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* min_delta_ns; void* max_delta_ns; int /*<<< orphan*/  mult; int /*<<< orphan*/  cpumask; } ;
struct TYPE_6__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ ; 
 scalar_t__ MCFINT_PIT1 ; 
 scalar_t__ MCFINT_VECBASE ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 TYPE_3__ cf_pit_clockevent ; 
 void* clockevent_delta2ns (int,TYPE_3__*) ; 
 int /*<<< orphan*/  clockevents_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  clocksource_hz2mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocksource_register (TYPE_1__*) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_sc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ pit_clk ; 
 int /*<<< orphan*/  pit_irq ; 
 int /*<<< orphan*/  setup_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void hw_timer_init(void)
{
	cf_pit_clockevent.cpumask = cpumask_of(smp_processor_id());
	cf_pit_clockevent.mult = div_sc(FREQ, NSEC_PER_SEC, 32);
	cf_pit_clockevent.max_delta_ns =
		clockevent_delta2ns(0xFFFF, &cf_pit_clockevent);
	cf_pit_clockevent.min_delta_ns =
		clockevent_delta2ns(0x3f, &cf_pit_clockevent);
	clockevents_register_device(&cf_pit_clockevent);

	setup_irq(MCFINT_VECBASE + MCFINT_PIT1, &pit_irq);

	pit_clk.mult = clocksource_hz2mult(FREQ, pit_clk.shift);
	clocksource_register(&pit_clk);
}