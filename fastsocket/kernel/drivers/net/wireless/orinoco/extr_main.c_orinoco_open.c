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
struct orinoco_private {int open; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __orinoco_up (struct orinoco_private*) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

int orinoco_open(struct net_device *dev)
{
	struct orinoco_private *priv = ndev_priv(dev);
	unsigned long flags;
	int err;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = __orinoco_up(priv);

	if (!err)
		priv->open = 1;

	orinoco_unlock(priv, &flags);

	return err;
}