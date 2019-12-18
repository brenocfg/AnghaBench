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
 int /*<<< orphan*/  IXDP2X01_INT_MASK_SET_REG ; 
 int /*<<< orphan*/  IXP2000_BOARD_IRQ_MASK (unsigned int) ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixdp2x01_irq_mask(unsigned int irq)
{
	ixp2000_reg_wrb(IXDP2X01_INT_MASK_SET_REG,
				IXP2000_BOARD_IRQ_MASK(irq));
}