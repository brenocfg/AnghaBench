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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct br2684_vcc {int dummy; } ;
struct br2684_dev {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 struct br2684_dev* BRPRIV (struct net_device*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  br2684_xmit_vcc (struct sk_buff*,struct net_device*,struct br2684_vcc*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  devs_lock ; 
 struct br2684_vcc* pick_outgoing_vcc (struct sk_buff*,struct br2684_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t br2684_start_xmit(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct br2684_dev *brdev = BRPRIV(dev);
	struct br2684_vcc *brvcc;

	pr_debug("br2684_start_xmit, skb_dst(skb)=%p\n", skb_dst(skb));
	read_lock(&devs_lock);
	brvcc = pick_outgoing_vcc(skb, brdev);
	if (brvcc == NULL) {
		pr_debug("no vcc attached to dev %s\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
		/* netif_stop_queue(dev); */
		dev_kfree_skb(skb);
		read_unlock(&devs_lock);
		return NETDEV_TX_OK;
	}
	if (!br2684_xmit_vcc(skb, dev, brvcc)) {
		/*
		 * We should probably use netif_*_queue() here, but that
		 * involves added complication.  We need to walk before
		 * we can run.
		 *
		 * Don't free here! this pointer might be no longer valid!
		 */
		dev->stats.tx_errors++;
		dev->stats.tx_fifo_errors++;
	}
	read_unlock(&devs_lock);
	return NETDEV_TX_OK;
}