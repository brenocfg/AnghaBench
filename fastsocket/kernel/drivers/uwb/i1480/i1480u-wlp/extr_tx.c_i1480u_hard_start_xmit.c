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
struct uwb_dev_addr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int flags; TYPE_1__ stats; } ;
struct i1480u {int /*<<< orphan*/  wlp; TYPE_2__* usb_iface; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int i1480u_xmit_frame (int /*<<< orphan*/ *,struct sk_buff*,struct uwb_dev_addr*) ; 
 struct i1480u* netdev_priv (struct net_device*) ; 
 int wlp_prepare_tx_frame (struct device*,int /*<<< orphan*/ *,struct sk_buff*,struct uwb_dev_addr*) ; 

netdev_tx_t i1480u_hard_start_xmit(struct sk_buff *skb,
					 struct net_device *net_dev)
{
	int result;
	struct i1480u *i1480u = netdev_priv(net_dev);
	struct device *dev = &i1480u->usb_iface->dev;
	struct uwb_dev_addr dst;

	if ((net_dev->flags & IFF_UP) == 0)
		goto error;
	result = wlp_prepare_tx_frame(dev, &i1480u->wlp, skb, &dst);
	if (result < 0) {
		dev_err(dev, "WLP verification of TX frame failed (%d). "
			"Dropping packet.\n", result);
		goto error;
	} else if (result == 1) {
		/* trans_start time will be set when WLP actually transmits
		 * the frame */
		goto out;
	}
	result = i1480u_xmit_frame(&i1480u->wlp, skb, &dst);
	if (result < 0) {
		dev_err(dev, "Frame TX failed (%d).\n", result);
		goto error;
	}
	return NETDEV_TX_OK;
error:
	dev_kfree_skb_any(skb);
	net_dev->stats.tx_dropped++;
out:
	return NETDEV_TX_OK;
}