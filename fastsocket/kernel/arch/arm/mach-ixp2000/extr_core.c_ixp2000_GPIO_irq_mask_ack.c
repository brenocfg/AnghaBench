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
 unsigned int IRQ_IXP2000_GPIO0 ; 
 int /*<<< orphan*/  IXP2000_GPIO_EDSR ; 
 int /*<<< orphan*/  IXP2000_GPIO_INCR ; 
 int /*<<< orphan*/  IXP2000_GPIO_INST ; 
 int /*<<< orphan*/  IXP2000_GPIO_LDSR ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixp2000_GPIO_irq_mask_ack(unsigned int irq)
{
	ixp2000_reg_write(IXP2000_GPIO_INCR, (1 << (irq - IRQ_IXP2000_GPIO0)));

	ixp2000_reg_write(IXP2000_GPIO_EDSR, (1 << (irq - IRQ_IXP2000_GPIO0)));
	ixp2000_reg_write(IXP2000_GPIO_LDSR, (1 << (irq - IRQ_IXP2000_GPIO0)));
	ixp2000_reg_wrb(IXP2000_GPIO_INST, (1 << (irq - IRQ_IXP2000_GPIO0)));
}