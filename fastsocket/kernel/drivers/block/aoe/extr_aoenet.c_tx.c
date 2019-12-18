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
struct sk_buff {struct net_device* dev; } ;
struct net_device {char* name; } ;

/* Variables and functions */
 scalar_t__ NET_XMIT_DROP ; 
 scalar_t__ dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  pr_warn (char*,char*,char*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skbtxq ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txlock ; 

__attribute__((used)) static int
tx(int id)
{
	struct sk_buff *skb;
	struct net_device *ifp;

	while ((skb = skb_dequeue(&skbtxq))) {
		spin_unlock_irq(&txlock);
		ifp = skb->dev;
		if (dev_queue_xmit(skb) == NET_XMIT_DROP && net_ratelimit())
			pr_warn("aoe: packet could not be sent on %s.  %s\n",
				ifp ? ifp->name : "netif",
				"consider increasing tx_queue_len");
		spin_lock_irq(&txlock);
	}
	return 0;
}