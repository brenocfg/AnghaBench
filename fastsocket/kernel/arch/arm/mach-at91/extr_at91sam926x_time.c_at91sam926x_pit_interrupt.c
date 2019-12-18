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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int AT91_PIT_PITS ; 
 int /*<<< orphan*/  AT91_PIT_PIVR ; 
 int /*<<< orphan*/  AT91_PIT_SR ; 
 scalar_t__ CLOCK_EVT_MODE_PERIODIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int PIT_PICNT (int) ; 
 int at91_sys_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ pit_clkevt ; 
 int /*<<< orphan*/  pit_cnt ; 
 scalar_t__ pit_cycle ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t at91sam926x_pit_interrupt(int irq, void *dev_id)
{

	/* The PIT interrupt may be disabled, and is shared */
	if ((pit_clkevt.mode == CLOCK_EVT_MODE_PERIODIC)
			&& (at91_sys_read(AT91_PIT_SR) & AT91_PIT_PITS)) {
		unsigned nr_ticks;

		/* Get number of ticks performed before irq, and ack it */
		nr_ticks = PIT_PICNT(at91_sys_read(AT91_PIT_PIVR));
		do {
			pit_cnt += pit_cycle;
			pit_clkevt.event_handler(&pit_clkevt);
			nr_ticks--;
		} while (nr_ticks);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}