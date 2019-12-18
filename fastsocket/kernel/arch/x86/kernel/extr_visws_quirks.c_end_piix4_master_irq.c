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
 int /*<<< orphan*/  cobalt_lock ; 
 int /*<<< orphan*/  enable_cobalt_irq (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void end_piix4_master_irq(unsigned int irq)
{
	unsigned long flags;

	spin_lock_irqsave(&cobalt_lock, flags);
	enable_cobalt_irq(irq);
	spin_unlock_irqrestore(&cobalt_lock, flags);
}