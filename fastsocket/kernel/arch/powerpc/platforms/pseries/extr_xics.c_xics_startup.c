#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ msi_desc; } ;

/* Variables and functions */
 TYPE_1__* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  unmask_msi_irq (unsigned int) ; 
 int /*<<< orphan*/  xics_unmask_irq (unsigned int) ; 

__attribute__((used)) static unsigned int xics_startup(unsigned int virq)
{
	/*
	 * The generic MSI code returns with the interrupt disabled on the
	 * card, using the MSI mask bits. Firmware doesn't appear to unmask
	 * at that level, so we do it here by hand.
	 */
	if (irq_to_desc(virq)->msi_desc)
		unmask_msi_irq(virq);

	/* unmask it */
	xics_unmask_irq(virq);
	return 0;
}