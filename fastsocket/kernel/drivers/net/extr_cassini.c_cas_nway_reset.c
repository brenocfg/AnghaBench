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
struct net_device {int dummy; } ;
struct cas {int link_cntl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cas_begin_auto_negotiation (struct cas*,int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cas_nway_reset(struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);
	unsigned long flags;

	if ((cp->link_cntl & BMCR_ANENABLE) == 0)
		return -EINVAL;

	/* Restart link process. */
	spin_lock_irqsave(&cp->lock, flags);
	cas_begin_auto_negotiation(cp, NULL);
	spin_unlock_irqrestore(&cp->lock, flags);

	return 0;
}