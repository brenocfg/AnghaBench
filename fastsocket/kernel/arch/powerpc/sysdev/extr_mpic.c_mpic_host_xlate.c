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
typedef  size_t u32 ;
struct irq_host {int dummy; } ;
struct device_node {int dummy; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned int,size_t,size_t,size_t,unsigned int) ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_NONE ; 
 scalar_t__ machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powermac ; 

__attribute__((used)) static int mpic_host_xlate(struct irq_host *h, struct device_node *ct,
			   u32 *intspec, unsigned int intsize,
			   irq_hw_number_t *out_hwirq, unsigned int *out_flags)

{
	static unsigned char map_mpic_senses[4] = {
		IRQ_TYPE_EDGE_RISING,
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
		IRQ_TYPE_EDGE_FALLING,
	};

	*out_hwirq = intspec[0];
	if (intsize > 1) {
		u32 mask = 0x3;

		/* Apple invented a new race of encoding on machines with
		 * an HT APIC. They encode, among others, the index within
		 * the HT APIC. We don't care about it here since thankfully,
		 * it appears that they have the APIC already properly
		 * configured, and thus our current fixup code that reads the
		 * APIC config works fine. However, we still need to mask out
		 * bits in the specifier to make sure we only get bit 0 which
		 * is the level/edge bit (the only sense bit exposed by Apple),
		 * as their bit 1 means something else.
		 */
		if (machine_is(powermac))
			mask = 0x1;
		*out_flags = map_mpic_senses[intspec[1] & mask];
	} else
		*out_flags = IRQ_TYPE_NONE;

	DBG("mpic: xlate (%d cells: 0x%08x 0x%08x) to line 0x%lx sense 0x%x\n",
	    intsize, intspec[0], intspec[1], *out_hwirq, *out_flags);

	return 0;
}