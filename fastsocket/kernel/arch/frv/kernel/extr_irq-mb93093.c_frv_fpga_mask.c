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
typedef  int uint16_t ;

/* Variables and functions */
 unsigned int IRQ_BASE_FPGA ; 
 int __get_IMR () ; 
 int /*<<< orphan*/  __set_IMR (int) ; 

__attribute__((used)) static void frv_fpga_mask(unsigned int irq)
{
	uint16_t imr = __get_IMR();

	imr |= 1 << (irq - IRQ_BASE_FPGA);
	__set_IMR(imr);
}