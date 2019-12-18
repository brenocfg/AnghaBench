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
typedef  scalar_t__ u32 ;
struct irq_host {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int MPC52xx_IRQ_L1_MASK ; 
 int MPC52xx_IRQ_L1_OFFSET ; 
 int MPC52xx_IRQ_L2_MASK ; 
 scalar_t__ mpc52xx_is_extirq (int,int) ; 
 unsigned int* mpc52xx_map_senses ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

__attribute__((used)) static int mpc52xx_irqhost_xlate(struct irq_host *h, struct device_node *ct,
				 u32 *intspec, unsigned int intsize,
				 irq_hw_number_t *out_hwirq,
				 unsigned int *out_flags)
{
	int intrvect_l1;
	int intrvect_l2;
	int intrvect_type;
	int intrvect_linux;

	if (intsize != 3)
		return -1;

	intrvect_l1 = (int)intspec[0];
	intrvect_l2 = (int)intspec[1];
	intrvect_type = (int)intspec[2] & 0x3;

	intrvect_linux = (intrvect_l1 << MPC52xx_IRQ_L1_OFFSET) &
			 MPC52xx_IRQ_L1_MASK;
	intrvect_linux |= intrvect_l2 & MPC52xx_IRQ_L2_MASK;

	*out_hwirq = intrvect_linux;
	*out_flags = IRQ_TYPE_LEVEL_LOW;
	if (mpc52xx_is_extirq(intrvect_l1, intrvect_l2))
		*out_flags = mpc52xx_map_senses[intrvect_type];

	pr_debug("return %x, l1=%d, l2=%d\n", intrvect_linux, intrvect_l1,
		 intrvect_l2);
	return 0;
}