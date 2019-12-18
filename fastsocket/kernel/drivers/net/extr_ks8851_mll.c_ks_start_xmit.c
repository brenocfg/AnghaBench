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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ks_net {int /*<<< orphan*/  statelock; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_disable_int (struct ks_net*) ; 
 int /*<<< orphan*/  ks_enable_int (struct ks_net*) ; 
 scalar_t__ ks_tx_fifo_space (struct ks_net*) ; 
 int /*<<< orphan*/  ks_write_qmu (struct ks_net*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ks_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	int retv = NETDEV_TX_OK;
	struct ks_net *ks = netdev_priv(netdev);

	disable_irq(netdev->irq);
	ks_disable_int(ks);
	spin_lock(&ks->statelock);

	/* Extra space are required:
	*  4 byte for alignment, 4 for status/length, 4 for CRC
	*/

	if (likely(ks_tx_fifo_space(ks) >= skb->len + 12)) {
		ks_write_qmu(ks, skb->data, skb->len);
		dev_kfree_skb(skb);
	} else
		retv = NETDEV_TX_BUSY;
	spin_unlock(&ks->statelock);
	ks_enable_int(ks);
	enable_irq(netdev->irq);
	return retv;
}