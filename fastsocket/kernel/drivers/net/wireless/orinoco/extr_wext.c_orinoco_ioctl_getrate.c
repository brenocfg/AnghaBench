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
struct orinoco_private {int /*<<< orphan*/  bitratemode; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int fixed; scalar_t__ disabled; } ;

/* Variables and functions */
 int EBUSY ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  orinoco_get_ratemode_cfg (int /*<<< orphan*/ ,int*,int*) ; 
 int orinoco_hw_get_act_bitrate (struct orinoco_private*,int*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_getrate(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rrq,
				 char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int err = 0;
	int bitrate, automatic;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	orinoco_get_ratemode_cfg(priv->bitratemode, &bitrate, &automatic);

	/* If the interface is running we try to find more about the
	   current mode */
	if (netif_running(dev)) {
		int act_bitrate;
		int lerr;

		/* Ignore errors if we can't get the actual bitrate */
		lerr = orinoco_hw_get_act_bitrate(priv, &act_bitrate);
		if (!lerr)
			bitrate = act_bitrate;
	}

	orinoco_unlock(priv, &flags);

	rrq->value = bitrate;
	rrq->fixed = !automatic;
	rrq->disabled = 0;

	return err;
}