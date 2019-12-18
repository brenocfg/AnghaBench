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
struct ifreq {int dummy; } ;
struct ax_device {int /*<<< orphan*/  mii_lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	struct ax_device *ax = to_ax_dev(dev);
	unsigned long flags;
	int rc;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irqsave(&ax->mii_lock, flags);
	rc = generic_mii_ioctl(&ax->mii, if_mii(req), cmd, NULL);
	spin_unlock_irqrestore(&ax->mii_lock, flags);

	return rc;
}