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
struct sk_buff {TYPE_1__* dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int priv_flags; int /*<<< orphan*/  ax25_ptr; } ;

/* Variables and functions */
 int IFF_OVS_DATAPATH ; 
 int deliver_skb (struct sk_buff*,struct packet_type*,struct net_device*) ; 
 struct sk_buff* openvswitch_handle_frame_hook (struct sk_buff*) ; 

__attribute__((used)) static inline struct sk_buff *handle_openvswitch(struct sk_buff *skb,
						 struct packet_type **pt_prev,
						 int *ret,
						 struct net_device *orig_dev)
{
	if (!(skb->dev->priv_flags & IFF_OVS_DATAPATH) || !skb->dev->ax25_ptr)
		return skb;

	if (*pt_prev) {
		*ret = deliver_skb(skb, *pt_prev, orig_dev);
		*pt_prev = NULL;
	}
	return openvswitch_handle_frame_hook(skb);
}