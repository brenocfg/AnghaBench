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
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mask_rm9k_irq (unsigned int) ; 

__attribute__((used)) static void local_rm9k_perfcounter_irq_shutdown(void *args)
{
	unsigned int irq = (unsigned int) args;
	unsigned long flags;

	local_irq_save(flags);
	mask_rm9k_irq(irq);
	local_irq_restore(flags);
}