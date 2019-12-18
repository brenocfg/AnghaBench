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
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int AT91_ST_ALMS ; 
 int /*<<< orphan*/  AT91_ST_IDR ; 
 int /*<<< orphan*/  AT91_ST_IER ; 
 int /*<<< orphan*/  AT91_ST_PIMR ; 
 int AT91_ST_PITS ; 
 int /*<<< orphan*/  AT91_ST_RTAR ; 
 int /*<<< orphan*/  AT91_ST_SR ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int LATCH ; 
 int /*<<< orphan*/  at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 
 int irqmask ; 
 int last_crtr ; 
 int read_CRTR () ; 

__attribute__((used)) static void
clkevt32k_mode(enum clock_event_mode mode, struct clock_event_device *dev)
{
	/* Disable and flush pending timer interrupts */
	at91_sys_write(AT91_ST_IDR, AT91_ST_PITS | AT91_ST_ALMS);
	(void) at91_sys_read(AT91_ST_SR);

	last_crtr = read_CRTR();
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		/* PIT for periodic irqs; fixed rate of 1/HZ */
		irqmask = AT91_ST_PITS;
		at91_sys_write(AT91_ST_PIMR, LATCH);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		/* ALM for oneshot irqs, set by next_event()
		 * before 32 seconds have passed
		 */
		irqmask = AT91_ST_ALMS;
		at91_sys_write(AT91_ST_RTAR, last_crtr);
		break;
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_RESUME:
		irqmask = 0;
		break;
	}
	at91_sys_write(AT91_ST_IER, irqmask);
}