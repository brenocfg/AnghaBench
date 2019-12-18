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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct i2400m {int /*<<< orphan*/  tx_lock; struct sk_buff* wake_tx_skb; int /*<<< orphan*/  wake_tx_ws; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct net_device*,struct i2400m*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct net_device*,struct i2400m*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_put (struct i2400m*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct i2400m* net_dev_to_i2400m (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static
int i2400m_stop(struct net_device *net_dev)
{
	struct i2400m *i2400m = net_dev_to_i2400m(net_dev);
	struct device *dev = i2400m_dev(i2400m);

	d_fnstart(3, dev, "(net_dev %p [i2400m %p])\n", net_dev, i2400m);
	/* See i2400m_hard_start_xmit(), references are taken there
	 * and here we release them if the work was still
	 * pending. Note we can't differentiate work not pending vs
	 * never scheduled, so the NULL check does that. */
	if (cancel_work_sync(&i2400m->wake_tx_ws) == 0
	    && i2400m->wake_tx_skb != NULL) {
		unsigned long flags;
		struct sk_buff *wake_tx_skb;
		spin_lock_irqsave(&i2400m->tx_lock, flags);
		wake_tx_skb = i2400m->wake_tx_skb;	/* compat help */
		i2400m->wake_tx_skb = NULL;	/* compat help */
		spin_unlock_irqrestore(&i2400m->tx_lock, flags);
		i2400m_put(i2400m);
		kfree_skb(wake_tx_skb);
	}
	d_fnend(3, dev, "(net_dev %p [i2400m %p]) = 0\n", net_dev, i2400m);
	return 0;
}