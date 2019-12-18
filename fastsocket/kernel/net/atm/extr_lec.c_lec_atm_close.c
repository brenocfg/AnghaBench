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
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct lec_priv {int /*<<< orphan*/ * lecd; } ;
struct atm_vcc {scalar_t__ proto_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lec_arp_destroy (struct lec_priv*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct lec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_atm (struct atm_vcc*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lec_atm_close(struct atm_vcc *vcc)
{
	struct sk_buff *skb;
	struct net_device *dev = (struct net_device *)vcc->proto_data;
	struct lec_priv *priv = netdev_priv(dev);

	priv->lecd = NULL;
	/* Do something needful? */

	netif_stop_queue(dev);
	lec_arp_destroy(priv);

	if (skb_peek(&sk_atm(vcc)->sk_receive_queue))
		printk("%s lec_atm_close: closing with messages pending\n",
		       dev->name);
	while ((skb = skb_dequeue(&sk_atm(vcc)->sk_receive_queue)) != NULL) {
		atm_return(vcc, skb->truesize);
		dev_kfree_skb(skb);
	}

	printk("%s: Shut down!\n", dev->name);
	module_put(THIS_MODULE);
}