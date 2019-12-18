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
 int EINVAL ; 
 size_t XILINX_INTC_MAXIRQS ; 
 void** xilinx_intc_map_senses ; 
 void** xilinx_intc_typetable ; 

__attribute__((used)) static int xilinx_intc_xlate(struct irq_host *h, struct device_node *ct,
				u32 *intspec, unsigned int intsize,
				irq_hw_number_t *out_hwirq,
				unsigned int *out_flags)
{
	if ((intsize < 2) || (intspec[0] >= XILINX_INTC_MAXIRQS))
		return -EINVAL;

	/* keep a copy of the interrupt type til the interrupt is mapped
	 */
	xilinx_intc_typetable[intspec[0]] = xilinx_intc_map_senses[intspec[1]];

	/* Xilinx uses 2 interrupt entries, the 1st being the h/w
	 * interrupt number, the 2nd being the interrupt type, edge or level
	 */
	*out_hwirq = intspec[0];
	*out_flags = xilinx_intc_map_senses[intspec[1]];

	return 0;
}