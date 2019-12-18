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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct TYPE_2__ {int (* read_bcr ) (int /*<<< orphan*/ ,int) ;} ;
struct pcnet32_private {scalar_t__ chip_version; int /*<<< orphan*/  lock; TYPE_1__ a; int /*<<< orphan*/  mii_if; scalar_t__ mii; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 scalar_t__ PCNET32_79C970A ; 
 int mii_link_ok (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 pcnet32_get_link(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long flags;
	int r;

	spin_lock_irqsave(&lp->lock, flags);
	if (lp->mii) {
		r = mii_link_ok(&lp->mii_if);
	} else if (lp->chip_version >= PCNET32_79C970A) {
		ulong ioaddr = dev->base_addr;	/* card base I/O address */
		r = (lp->a.read_bcr(ioaddr, 4) != 0xc0);
	} else {	/* can not detect link on really old chips */
		r = 1;
	}
	spin_unlock_irqrestore(&lp->lock, flags);

	return r;
}