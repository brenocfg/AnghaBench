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
 int /*<<< orphan*/  mask_msi_irq (unsigned int) ; 
 int /*<<< orphan*/  mpic_mask_irq (unsigned int) ; 

__attribute__((used)) static void mpic_u3msi_mask_irq(unsigned int irq)
{
	mask_msi_irq(irq);
	mpic_mask_irq(irq);
}