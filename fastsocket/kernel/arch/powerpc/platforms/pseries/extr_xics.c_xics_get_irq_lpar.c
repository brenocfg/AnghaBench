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
 unsigned int NO_IRQ ; 
 unsigned int XICS_IRQ_SPURIOUS ; 
 unsigned int irq_radix_revmap_lookup (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (int) ; 
 unsigned int lpar_xirr_info_get () ; 
 int /*<<< orphan*/  lpar_xirr_info_set (unsigned int) ; 
 int /*<<< orphan*/  xics_host ; 
 int /*<<< orphan*/  xics_mask_unknown_vec (unsigned int) ; 
 unsigned int xics_xirr_vector (unsigned int) ; 

__attribute__((used)) static unsigned int xics_get_irq_lpar(void)
{
	unsigned int xirr = lpar_xirr_info_get();
	unsigned int vec = xics_xirr_vector(xirr);
	unsigned int irq;

	if (vec == XICS_IRQ_SPURIOUS)
		return NO_IRQ;

	irq = irq_radix_revmap_lookup(xics_host, vec);
	if (likely(irq != NO_IRQ))
		return irq;

	/* We don't have a linux mapping, so have RTAS mask it. */
	xics_mask_unknown_vec(vec);

	/* We might learn about it later, so EOI it */
	lpar_xirr_info_set(xirr);
	return NO_IRQ;
}