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
 unsigned int ASSABET_BCR ; 
 unsigned int BCR_value ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void ASSABET_BCR_frob(unsigned int mask, unsigned int val)
{
	unsigned long flags;

	local_irq_save(flags);
	BCR_value = (BCR_value & ~mask) | val;
	ASSABET_BCR = BCR_value;
	local_irq_restore(flags);
}