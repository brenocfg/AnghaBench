#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct fs_enet_private {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* adjust_link ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  generic_adjust_link (struct net_device*) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static void fs_adjust_link(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&fep->lock, flags);

	if(fep->ops->adjust_link)
		fep->ops->adjust_link(dev);
	else
		generic_adjust_link(dev);

	spin_unlock_irqrestore(&fep->lock, flags);
}