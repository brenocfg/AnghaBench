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
struct TYPE_7__ {TYPE_1__* netdev; struct TYPE_7__* last; struct TYPE_7__* next; scalar_t__ master; } ;
typedef  TYPE_2__ isdn_net_local ;
struct TYPE_6__ {int /*<<< orphan*/  queue_lock; TYPE_2__* local; TYPE_2__* queue; } ;

/* Variables and functions */
 TYPE_2__* ISDN_MASTER_PRIV (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ void isdn_net_rm_from_bundle(isdn_net_local *lp)
{
	isdn_net_local *master_lp = lp;
	unsigned long flags;

	if (lp->master)
		master_lp = ISDN_MASTER_PRIV(lp);

//	printk(KERN_DEBUG "%s: lp:%s(%p) mlp:%s(%p) last(%p) next(%p) mndq(%p)\n",
//		__func__, lp->name, lp, master_lp->name, master_lp, lp->last, lp->next, master_lp->netdev->queue);
	spin_lock_irqsave(&master_lp->netdev->queue_lock, flags);
	lp->last->next = lp->next;
	lp->next->last = lp->last;
	if (master_lp->netdev->queue == lp) {
		master_lp->netdev->queue = lp->next;
		if (lp->next == lp) { /* last in queue */
			master_lp->netdev->queue = master_lp->netdev->local;
		}
	}
	lp->next = lp->last = lp;	/* (re)set own pointers */
//	printk(KERN_DEBUG "%s: mndq(%p)\n",
//		__func__, master_lp->netdev->queue);
	spin_unlock_irqrestore(&master_lp->netdev->queue_lock, flags);
}