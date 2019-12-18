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
 unsigned char readl (unsigned long*) ; 
 int /*<<< orphan*/  writel (unsigned long,unsigned long*) ; 

__attribute__((used)) static void gpio_write_bit(unsigned long *port, unsigned char data, int bit,
	unsigned char clk_mask, unsigned char data_mask)
{
	unsigned long shadow = readl(port) & ~clk_mask;
	writel(shadow, port);
	if (data & 1 << bit)
		shadow |= data_mask;
	else
		shadow &= ~data_mask;
	writel(shadow, port);
	/* For FPGA: min 5.0ns (DCC) before CCLK high */
	shadow |= clk_mask;
	writel(shadow, port);
}