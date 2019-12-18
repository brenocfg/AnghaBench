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

/* Variables and functions */
 int ETIME ; 
 int MIN_OSCR_DELTA ; 
 int /*<<< orphan*/  OIER ; 
 int /*<<< orphan*/  OIER_E0 ; 
 unsigned long OSCR ; 
 unsigned long OSMR0 ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static int
sa1100_osmr0_set_next_event(unsigned long delta, struct clock_event_device *c)
{
	unsigned long flags, next, oscr;

	raw_local_irq_save(flags);
	OIER |= OIER_E0;
	next = OSCR + delta;
	OSMR0 = next;
	oscr = OSCR;
	raw_local_irq_restore(flags);

	return (signed)(next - oscr) <= MIN_OSCR_DELTA ? -ETIME : 0;
}