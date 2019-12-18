#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  xmit_lock; struct TYPE_6__* next; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_7__ {int /*<<< orphan*/  queue_lock; TYPE_1__* queue; } ;
typedef  TYPE_2__ isdn_net_dev ;

/* Variables and functions */
 scalar_t__ isdn_net_lp_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ isdn_net_local * isdn_net_get_locked_lp(isdn_net_dev *nd)
{
	unsigned long flags;
	isdn_net_local *lp;

	spin_lock_irqsave(&nd->queue_lock, flags);
	lp = nd->queue;         /* get lp on top of queue */
	while (isdn_net_lp_busy(nd->queue)) {
		nd->queue = nd->queue->next;
		if (nd->queue == lp) { /* not found -- should never happen */
			lp = NULL;
			goto errout;
		}
	}
	lp = nd->queue;
	nd->queue = nd->queue->next;
	spin_unlock_irqrestore(&nd->queue_lock, flags);
	spin_lock(&lp->xmit_lock);
	local_bh_disable();
	return lp;
errout:
	spin_unlock_irqrestore(&nd->queue_lock, flags);
	return lp;
}