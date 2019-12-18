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
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long titan_cached_irq_mask ; 
 int /*<<< orphan*/  titan_irq_lock ; 
 int /*<<< orphan*/  titan_update_irq_hw (unsigned long) ; 

__attribute__((used)) static inline void
titan_enable_irq(unsigned int irq)
{
	spin_lock(&titan_irq_lock);
	titan_cached_irq_mask |= 1UL << (irq - 16);
	titan_update_irq_hw(titan_cached_irq_mask);
	spin_unlock(&titan_irq_lock);
}