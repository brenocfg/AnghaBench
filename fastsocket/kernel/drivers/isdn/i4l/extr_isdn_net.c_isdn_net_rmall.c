#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* netdev; } ;
struct TYPE_5__ {TYPE_1__* local; } ;
struct TYPE_4__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 TYPE_3__* dev ; 
 int isdn_net_realrm (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
isdn_net_rmall(void)
{
	u_long flags;
	int ret;

	/* Walk through netdev-chain */
	spin_lock_irqsave(&dev->lock, flags);
	while (dev->netdev) {
		if (!dev->netdev->local->master) {
			/* Remove master-devices only, slaves get removed with their master */
			spin_unlock_irqrestore(&dev->lock, flags);
			if ((ret = isdn_net_realrm(dev->netdev, NULL))) {
				return ret;
			}
			spin_lock_irqsave(&dev->lock, flags);
		}
	}
	dev->netdev = NULL;
	spin_unlock_irqrestore(&dev->lock, flags);
	return 0;
}