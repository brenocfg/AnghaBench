#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_7__ {scalar_t__ next; TYPE_1__* dev; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_8__ {TYPE_2__* netdev; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ISDN_TIMER_NETHANGUP ; 
 TYPE_5__* dev ; 
 int isdn_net_realrm (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int
isdn_net_rm(char *name)
{
	u_long flags;
	isdn_net_dev *p;
	isdn_net_dev *q;

	/* Search name in netdev-chain */
	spin_lock_irqsave(&dev->lock, flags);
	p = dev->netdev;
	q = NULL;
	while (p) {
		if (!strcmp(p->dev->name, name)) {
			spin_unlock_irqrestore(&dev->lock, flags);
			return (isdn_net_realrm(p, q));
		}
		q = p;
		p = (isdn_net_dev *) p->next;
	}
	spin_unlock_irqrestore(&dev->lock, flags);
	/* If no more net-devices remain, disable auto-hangup timer */
	if (dev->netdev == NULL)
		isdn_timer_ctrl(ISDN_TIMER_NETHANGUP, 0);
	return -ENODEV;
}