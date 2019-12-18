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
 unsigned long __irq_mask ; 

__attribute__((used)) static void __default_power_switch_setup(void)
{
	/* default is to mask all interrupt sources. */
	__irq_mask = *(unsigned long *)0xfeff9820;
	*(unsigned long *)0xfeff9820 = 0xfffe0000;
}