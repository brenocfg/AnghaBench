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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sonic_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t macsonic_interrupt(int irq, void *dev_id)
{
	irqreturn_t result;
	unsigned long flags;

	local_irq_save(flags);
	result = sonic_interrupt(irq, dev_id);
	local_irq_restore(flags);
	return result;
}