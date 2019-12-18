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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct mv643xx_eth_private {int int_mask; int rxq_count; int txq_count; scalar_t__ rxq; scalar_t__ txq; TYPE_1__ rx_oom; scalar_t__ oom; int /*<<< orphan*/  rx_recycle; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int HZ ; 
 int /*<<< orphan*/  INT_CAUSE ; 
 int /*<<< orphan*/  INT_CAUSE_EXT ; 
 int INT_EXT ; 
 int INT_EXT_LINK_PHY ; 
 int INT_EXT_TX ; 
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  INT_MASK_EXT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int INT_RX_0 ; 
 int INT_TX_END_0 ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mv643xx_eth_irq ; 
 int /*<<< orphan*/  mv643xx_eth_recalc_skb_size (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  port_start (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rxq_deinit (scalar_t__) ; 
 int rxq_init (struct mv643xx_eth_private*,int) ; 
 int /*<<< orphan*/  rxq_refill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txq_deinit (scalar_t__) ; 
 int txq_init (struct mv643xx_eth_private*,int) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv643xx_eth_open(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	int err;
	int i;

	wrlp(mp, INT_CAUSE, 0);
	wrlp(mp, INT_CAUSE_EXT, 0);
	rdlp(mp, INT_CAUSE_EXT);

	err = request_irq(dev->irq, mv643xx_eth_irq,
			  IRQF_SHARED, dev->name, dev);
	if (err) {
		dev_printk(KERN_ERR, &dev->dev, "can't assign irq\n");
		return -EAGAIN;
	}

	mv643xx_eth_recalc_skb_size(mp);

	napi_enable(&mp->napi);

	skb_queue_head_init(&mp->rx_recycle);

	mp->int_mask = INT_EXT;

	for (i = 0; i < mp->rxq_count; i++) {
		err = rxq_init(mp, i);
		if (err) {
			while (--i >= 0)
				rxq_deinit(mp->rxq + i);
			goto out;
		}

		rxq_refill(mp->rxq + i, INT_MAX);
		mp->int_mask |= INT_RX_0 << i;
	}

	if (mp->oom) {
		mp->rx_oom.expires = jiffies + (HZ / 10);
		add_timer(&mp->rx_oom);
	}

	for (i = 0; i < mp->txq_count; i++) {
		err = txq_init(mp, i);
		if (err) {
			while (--i >= 0)
				txq_deinit(mp->txq + i);
			goto out_free;
		}
		mp->int_mask |= INT_TX_END_0 << i;
	}

	port_start(mp);

	wrlp(mp, INT_MASK_EXT, INT_EXT_LINK_PHY | INT_EXT_TX);
	wrlp(mp, INT_MASK, mp->int_mask);

	return 0;


out_free:
	for (i = 0; i < mp->rxq_count; i++)
		rxq_deinit(mp->rxq + i);
out:
	free_irq(dev->irq, dev);

	return err;
}