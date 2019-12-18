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
struct ns83820 {int /*<<< orphan*/  misc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ns83820_update_stats (struct ns83820*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ns83820_mib_isr(struct ns83820 *dev)
{
	unsigned long flags;
	spin_lock_irqsave(&dev->misc_lock, flags);
	ns83820_update_stats(dev);
	spin_unlock_irqrestore(&dev->misc_lock, flags);
}