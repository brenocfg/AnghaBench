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
typedef  unsigned long u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ST_RTAR ; 
 int /*<<< orphan*/  AT91_ST_SR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  raw_irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 unsigned long read_CRTR () ; 

__attribute__((used)) static int
clkevt32k_next_event(unsigned long delta, struct clock_event_device *dev)
{
	unsigned long	flags;
	u32		alm;
	int		status = 0;

	BUG_ON(delta < 2);

	/* Use "raw" primitives so we behave correctly on RT kernels. */
	raw_local_irq_save(flags);

	/*
	 * According to Thomas Gleixner irqs are already disabled here.  Simply
	 * removing raw_local_irq_save above (and the matching
	 * raw_local_irq_restore) was not accepted.  See
	 * http://thread.gmane.org/gmane.linux.ports.arm.kernel/41174
	 * So for now (2008-11-20) just warn once if irqs were not disabled ...
	 */
	WARN_ON_ONCE(!raw_irqs_disabled_flags(flags));

	/* The alarm IRQ uses absolute time (now+delta), not the relative
	 * time (delta) in our calling convention.  Like all clockevents
	 * using such "match" hardware, we have a race to defend against.
	 *
	 * Our defense here is to have set up the clockevent device so the
	 * delta is at least two.  That way we never end up writing RTAR
	 * with the value then held in CRTR ... which would mean the match
	 * wouldn't trigger until 32 seconds later, after CRTR wraps.
	 */
	alm = read_CRTR();

	/* Cancel any pending alarm; flush any pending IRQ */
	at91_sys_write(AT91_ST_RTAR, alm);
	(void) at91_sys_read(AT91_ST_SR);

	/* Schedule alarm by writing RTAR. */
	alm += delta;
	at91_sys_write(AT91_ST_RTAR, alm);

	raw_local_irq_restore(flags);
	return status;
}