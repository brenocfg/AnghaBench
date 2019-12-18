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
typedef  int u8 ;
struct sock {int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct net_device {int mc_count; int flags; int* broadcast; struct dev_mc_list* mc_list; int /*<<< orphan*/  name; } ;
struct dev_mc_list {int* dmi_addr; struct dev_mc_list* next; } ;
struct bnep_set_filter_req {void* len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  type; } ;
struct bnep_session {TYPE_1__* sock; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNEP_CONTROL ; 
 int /*<<< orphan*/  BNEP_FILTER_MULTI_ADDR_SET ; 
 int BNEP_MAX_MULTICAST_FILTERS ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct bnep_session* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnep_net_set_mc_list(struct net_device *dev)
{
#ifdef CONFIG_BT_BNEP_MC_FILTER
	struct bnep_session *s = netdev_priv(dev);
	struct sock *sk = s->sock->sk;
	struct bnep_set_filter_req *r;
	struct sk_buff *skb;
	int size;

	BT_DBG("%s mc_count %d", dev->name, dev->mc_count);

	size = sizeof(*r) + (BNEP_MAX_MULTICAST_FILTERS + 1) * ETH_ALEN * 2;
	skb  = alloc_skb(size, GFP_ATOMIC);
	if (!skb) {
		BT_ERR("%s Multicast list allocation failed", dev->name);
		return;
	}

	r = (void *) skb->data;
	__skb_put(skb, sizeof(*r));

	r->type = BNEP_CONTROL;
	r->ctrl = BNEP_FILTER_MULTI_ADDR_SET;

	if (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		u8 start[ETH_ALEN] = { 0x01 };

		/* Request all addresses */
		memcpy(__skb_put(skb, ETH_ALEN), start, ETH_ALEN);
		memcpy(__skb_put(skb, ETH_ALEN), dev->broadcast, ETH_ALEN);
		r->len = htons(ETH_ALEN * 2);
	} else {
		struct dev_mc_list *dmi = dev->mc_list;
		int i, len = skb->len;

		if (dev->flags & IFF_BROADCAST) {
			memcpy(__skb_put(skb, ETH_ALEN), dev->broadcast, ETH_ALEN);
			memcpy(__skb_put(skb, ETH_ALEN), dev->broadcast, ETH_ALEN);
		}

		/* FIXME: We should group addresses here. */

		for (i = 0; i < dev->mc_count && i < BNEP_MAX_MULTICAST_FILTERS; i++) {
			memcpy(__skb_put(skb, ETH_ALEN), dmi->dmi_addr, ETH_ALEN);
			memcpy(__skb_put(skb, ETH_ALEN), dmi->dmi_addr, ETH_ALEN);
			dmi = dmi->next;
		}
		r->len = htons(skb->len - len);
	}

	skb_queue_tail(&sk->sk_write_queue, skb);
	wake_up_interruptible(sk->sk_sleep);
#endif
}