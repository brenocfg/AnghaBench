#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; TYPE_2__* netdev; scalar_t__ master; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_8__ {int /*<<< orphan*/  queue_lock; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_9__ {TYPE_2__* netdev; } ;

/* Variables and functions */
 TYPE_5__* ISDN_MASTER_PRIV (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_net_lp_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ int isdn_net_device_busy(isdn_net_local *lp)
{
	isdn_net_local *nlp;
	isdn_net_dev *nd;
	unsigned long flags;

	if (!isdn_net_lp_busy(lp))
		return 0;

	if (lp->master)
		nd = ISDN_MASTER_PRIV(lp)->netdev;
	else
		nd = lp->netdev;
	
	spin_lock_irqsave(&nd->queue_lock, flags);
	nlp = lp->next;
	while (nlp != lp) {
		if (!isdn_net_lp_busy(nlp)) {
			spin_unlock_irqrestore(&nd->queue_lock, flags);
			return 0;
		}
		nlp = nlp->next;
	}
	spin_unlock_irqrestore(&nd->queue_lock, flags);
	return 1;
}