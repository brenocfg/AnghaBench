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
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {scalar_t__ pkt_type; scalar_t__ len; int /*<<< orphan*/ * next; scalar_t__ data; } ;
struct packet_type {scalar_t__ af_packet_priv; } ;
struct net_device {int dummy; } ;
struct eth_bearer {int bearer; } ;

/* Variables and functions */
 scalar_t__ PACKET_BROADCAST ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_recv_msg (struct sk_buff*,int) ; 

__attribute__((used)) static int recv_msg(struct sk_buff *buf, struct net_device *dev,
		    struct packet_type *pt, struct net_device *orig_dev)
{
	struct eth_bearer *eb_ptr = (struct eth_bearer *)pt->af_packet_priv;
	u32 size;

	if (!net_eq(dev_net(dev), &init_net)) {
		kfree_skb(buf);
		return 0;
	}

	if (likely(eb_ptr->bearer)) {
		if (likely(buf->pkt_type <= PACKET_BROADCAST)) {
			size = msg_size((struct tipc_msg *)buf->data);
			skb_trim(buf, size);
			if (likely(buf->len == size)) {
				buf->next = NULL;
				tipc_recv_msg(buf, eb_ptr->bearer);
				return 0;
			}
		}
	}
	kfree_skb(buf);
	return 0;
}