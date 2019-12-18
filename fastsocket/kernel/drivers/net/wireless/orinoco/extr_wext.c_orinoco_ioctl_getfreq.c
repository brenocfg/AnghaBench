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
struct orinoco_private {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int m; int e; } ;

/* Variables and functions */
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int orinoco_hw_get_freq (struct orinoco_private*) ; 

__attribute__((used)) static int orinoco_ioctl_getfreq(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_freq *frq,
				 char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int tmp;

	/* Locking done in there */
	tmp = orinoco_hw_get_freq(priv);
	if (tmp < 0)
		return tmp;

	frq->m = tmp * 100000;
	frq->e = 1;

	return 0;
}