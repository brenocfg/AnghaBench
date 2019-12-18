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
 unsigned long HSR0_CBM ; 
 unsigned long HSR0_DCE ; 
 unsigned long __get_HSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_HSR (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void frv_change_dcache_mode(unsigned long newmode)
{
	unsigned long flags, hsr0;

	local_irq_save(flags);

	hsr0 = __get_HSR(0);
	hsr0 &= ~HSR0_DCE;
	__set_HSR(0, hsr0);

	asm volatile("	dcef	@(gr0,gr0),#1	\n"
		     "	membar			\n"
		     : : : "memory"
		     );

	hsr0 = (hsr0 & ~HSR0_CBM) | newmode;
	__set_HSR(0, hsr0);
	hsr0 |= HSR0_DCE;
	__set_HSR(0, hsr0);

	local_irq_restore(flags);

	//printk("HSR0 now %08lx\n", hsr0);
}