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
typedef  int uint32_t ;

/* Variables and functions */
 int mdp_irq_mask ; 
 int /*<<< orphan*/  mdp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static uint32_t mdp_check_mask(uint32_t mask)
{
	uint32_t ret;
	unsigned long irq_flags;

	spin_lock_irqsave(&mdp_lock, irq_flags);
	ret = mdp_irq_mask & mask;
	spin_unlock_irqrestore(&mdp_lock, irq_flags);
	return ret;
}