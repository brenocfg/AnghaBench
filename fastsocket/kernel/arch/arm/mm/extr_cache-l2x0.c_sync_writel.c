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
 scalar_t__ l2x0_base ; 
 int /*<<< orphan*/  l2x0_lock ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void sync_writel(unsigned long val, unsigned long reg,
			       unsigned long complete_mask)
{
	unsigned long flags;

	spin_lock_irqsave(&l2x0_lock, flags);
	writel(val, l2x0_base + reg);
	/* wait for the operation to complete */
	while (readl(l2x0_base + reg) & complete_mask)
		;
	spin_unlock_irqrestore(&l2x0_lock, flags);
}