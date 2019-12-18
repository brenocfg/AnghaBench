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
 unsigned int LUB_MISC_WR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void lubbock_set_misc_wr(unsigned int mask, unsigned int set)
{
	unsigned long flags;

	local_irq_save(flags);
	LUB_MISC_WR = (LUB_MISC_WR & ~mask) | (set & mask);
	local_irq_restore(flags);
}