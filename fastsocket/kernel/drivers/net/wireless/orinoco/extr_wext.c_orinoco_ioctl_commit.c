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
struct orinoco_private {int /*<<< orphan*/  open; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int orinoco_commit (struct orinoco_private*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_commit(struct net_device *dev,
				struct iw_request_info *info,
				void *wrqu,
				char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	unsigned long flags;
	int err = 0;

	if (!priv->open)
		return 0;

	if (orinoco_lock(priv, &flags) != 0)
		return err;

	err = orinoco_commit(priv);

	orinoco_unlock(priv, &flags);
	return err;
}