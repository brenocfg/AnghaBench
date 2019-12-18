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
 int IRQ_XIRQ2_LEVEL ; 
 unsigned long imask ; 

__attribute__((used)) static void mb93093_power_switch_setup(void)
{
	/* mask all but FPGA interrupt sources. */
	imask = *(volatile unsigned long *)0xfeff9820;
	*(volatile unsigned long *)0xfeff9820 = ~(1 << (IRQ_XIRQ2_LEVEL + 16)) & 0xfffe0000;
}