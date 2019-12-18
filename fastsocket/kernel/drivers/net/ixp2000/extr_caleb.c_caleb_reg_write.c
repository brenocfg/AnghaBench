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
typedef  int /*<<< orphan*/  volatile u8 ;

/* Variables and functions */
 scalar_t__ ENP2611_CALEB_VIRT_BASE ; 

__attribute__((used)) static void caleb_reg_write(int reg, u8 value)
{
	u8 dummy;

//	printk(KERN_INFO "caleb_reg_write(%d, %.2x)\n", reg, value);

	*((volatile u8 *)(ENP2611_CALEB_VIRT_BASE + reg)) = value;

	dummy = *((volatile u8 *)ENP2611_CALEB_VIRT_BASE);
	__asm__ __volatile__("mov %0, %0" : "+r" (dummy));
}