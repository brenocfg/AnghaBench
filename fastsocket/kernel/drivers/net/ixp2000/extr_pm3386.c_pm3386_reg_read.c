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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ ENP2611_PM3386_0_VIRT_BASE ; 
 scalar_t__ ENP2611_PM3386_1_VIRT_BASE ; 

__attribute__((used)) static u16 pm3386_reg_read(int pm, int reg)
{
	void *_reg;
	u16 value;

	_reg = (void *)ENP2611_PM3386_0_VIRT_BASE;
	if (pm == 1)
		_reg = (void *)ENP2611_PM3386_1_VIRT_BASE;

	value = *((volatile u16 *)(_reg + (reg << 1)));

//	printk(KERN_INFO "pm3386_reg_read(%d, %.3x) = %.8x\n", pm, reg, value);

	return value;
}