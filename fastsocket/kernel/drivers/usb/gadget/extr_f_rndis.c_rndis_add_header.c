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
struct rndis_packet_msg_type {int dummy; } ;
struct gether {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rndis_add_hdr (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *rndis_add_header(struct gether *port,
					struct sk_buff *skb)
{
	struct sk_buff *skb2;

	skb2 = skb_realloc_headroom(skb, sizeof(struct rndis_packet_msg_type));
	if (skb2)
		rndis_add_hdr(skb2);

	dev_kfree_skb_any(skb);
	return skb2;
}