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
 unsigned long ctrl_inl (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 scalar_t__ systemh_irq_mask_register ; 
 scalar_t__ systemh_irq_request_register ; 

__attribute__((used)) static void disable_systemh_irq(unsigned int irq)
{
	if (systemh_irq_mask_register) {
		unsigned long val, mask = 0x01 << 1;

		/* Clear the "irq"th bit in the mask and set it in the request */
		val = ctrl_inl((unsigned long)systemh_irq_mask_register);
		val &= ~mask;
		ctrl_outl(val, (unsigned long)systemh_irq_mask_register);

		val = ctrl_inl((unsigned long)systemh_irq_request_register);
		val |= mask;
		ctrl_outl(val, (unsigned long)systemh_irq_request_register);
	}
}