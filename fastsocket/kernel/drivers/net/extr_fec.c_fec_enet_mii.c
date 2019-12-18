#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct fec_enet_private {int /*<<< orphan*/  mii_lock; scalar_t__ hwp; } ;
struct TYPE_4__ {int /*<<< orphan*/  mii_regval; struct TYPE_4__* mii_next; int /*<<< orphan*/  (* mii_func ) (int /*<<< orphan*/ ,struct net_device*) ;} ;
typedef  TYPE_1__ mii_list_t ;

/* Variables and functions */
 scalar_t__ FEC_MII_DATA ; 
 TYPE_1__* mii_free ; 
 TYPE_1__* mii_head ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
fec_enet_mii(struct net_device *dev)
{
	struct	fec_enet_private *fep;
	mii_list_t	*mip;

	fep = netdev_priv(dev);
	spin_lock(&fep->mii_lock);

	if ((mip = mii_head) == NULL) {
		printk("MII and no head!\n");
		goto unlock;
	}

	if (mip->mii_func != NULL)
		(*(mip->mii_func))(readl(fep->hwp + FEC_MII_DATA), dev);

	mii_head = mip->mii_next;
	mip->mii_next = mii_free;
	mii_free = mip;

	if ((mip = mii_head) != NULL)
		writel(mip->mii_regval, fep->hwp + FEC_MII_DATA);

unlock:
	spin_unlock(&fep->mii_lock);
}