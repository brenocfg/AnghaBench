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
 int PLX9050_LINTI1_ACTIVE_HIGH ; 
 int PLX9050_LINTI1_ENABLE ; 
 int PLX9050_LINTI2_ACTIVE_HIGH ; 
 int PLX9050_LINTI2_ENABLE ; 
 int PLX9050_PCI_INTERRUPT_ENABLE ; 
 scalar_t__ PLX9050_REGISTER_INTERRUPT_CONTROL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void plx9050_interrupt_control(unsigned long io_base,
				      bool LINTi1_enable,
				      bool LINTi1_active_high,
				      bool LINTi2_enable,
				      bool LINTi2_active_high,
				      bool interrupt_enable)
{
	int flags = 0;

	if (LINTi1_enable)
		flags |= PLX9050_LINTI1_ENABLE;
	if (LINTi1_active_high)
		flags |= PLX9050_LINTI1_ACTIVE_HIGH;
	if (LINTi2_enable)
		flags |= PLX9050_LINTI2_ENABLE;
	if (LINTi2_active_high)
		flags |= PLX9050_LINTI2_ACTIVE_HIGH;

	if (interrupt_enable)
		flags |= PLX9050_PCI_INTERRUPT_ENABLE;

	outb(flags, io_base + PLX9050_REGISTER_INTERRUPT_CONTROL);
}