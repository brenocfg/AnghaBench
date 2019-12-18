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
typedef  int uint32_t ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_INT_MASK_REG ; 
 int /*<<< orphan*/  CPLD_INT_STATUS_REG ; 
 int MXC_EXP_IO_BASE ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 

__attribute__((used)) static void mx31pdk_expio_irq_handler(uint32_t irq, struct irq_desc *desc)
{
	uint32_t imr_val;
	uint32_t int_valid;
	uint32_t expio_irq;

	imr_val = __raw_readw(CPLD_INT_MASK_REG);
	int_valid = __raw_readw(CPLD_INT_STATUS_REG) & ~imr_val;

	expio_irq = MXC_EXP_IO_BASE;
	for (; int_valid != 0; int_valid >>= 1, expio_irq++) {
		if ((int_valid & 1) == 0)
			continue;
		generic_handle_irq(expio_irq);
	}
}