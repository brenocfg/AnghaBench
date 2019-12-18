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
 int /*<<< orphan*/ * IXDP2351_CPLD_INTA_MASK_SET_REG ; 
 int /*<<< orphan*/  IXDP2351_INTA_IRQ_MASK (unsigned int) ; 

__attribute__((used)) static void ixdp2351_inta_mask(unsigned int irq)
{
	*IXDP2351_CPLD_INTA_MASK_SET_REG = IXDP2351_INTA_IRQ_MASK(irq);
}