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
struct pmu_private {scalar_t__ rb_get; scalar_t__ rb_put; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
struct file {struct pmu_private* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int
pmu_fpoll(struct file *filp, poll_table *wait)
{
	struct pmu_private *pp = filp->private_data;
	unsigned int mask = 0;
	unsigned long flags;
	
	if (pp == 0)
		return 0;
	poll_wait(filp, &pp->wait, wait);
	spin_lock_irqsave(&pp->lock, flags);
	if (pp->rb_get != pp->rb_put)
		mask |= POLLIN;
	spin_unlock_irqrestore(&pp->lock, flags);
	return mask;
}