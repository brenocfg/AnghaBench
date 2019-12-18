#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {struct lbs_private* ml_priv; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; int /*<<< orphan*/  dev_addr; } ;
struct lbs_private {struct net_device* rtap_net_dev; TYPE_2__* dev; int /*<<< orphan*/  current_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtap_netdev_ops ; 

__attribute__((used)) static int lbs_add_rtap(struct lbs_private *priv)
{
	int ret = 0;
	struct net_device *rtap_dev;

	lbs_deb_enter(LBS_DEB_MAIN);
	if (priv->rtap_net_dev) {
		ret = -EPERM;
		goto out;
	}

	rtap_dev = alloc_netdev(0, "rtap%d", ether_setup);
	if (rtap_dev == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	memcpy(rtap_dev->dev_addr, priv->current_addr, ETH_ALEN);
	rtap_dev->type = ARPHRD_IEEE80211_RADIOTAP;
	rtap_dev->netdev_ops = &rtap_netdev_ops;
	rtap_dev->ml_priv = priv;
	SET_NETDEV_DEV(rtap_dev, priv->dev->dev.parent);

	ret = register_netdev(rtap_dev);
	if (ret) {
		free_netdev(rtap_dev);
		goto out;
	}
	priv->rtap_net_dev = rtap_dev;

out:
	lbs_deb_leave_args(LBS_DEB_MAIN, "ret %d", ret);
	return ret;
}