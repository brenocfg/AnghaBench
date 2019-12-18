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
struct tcphdr {int dummy; } ;
struct sk_buff {struct sk_buff* next; scalar_t__ truesize; scalar_t__ len; } ;
struct net_lro_desc {struct sk_buff* last_skb; struct sk_buff* parent; } ;
struct iphdr {int dummy; } ;
struct TYPE_2__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int TCP_PAYLOAD_LENGTH (struct iphdr*,struct tcphdr*) ; 
 int /*<<< orphan*/  lro_add_common (struct net_lro_desc*,struct iphdr*,struct tcphdr*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void lro_add_packet(struct net_lro_desc *lro_desc, struct sk_buff *skb,
			   struct iphdr *iph, struct tcphdr *tcph)
{
	struct sk_buff *parent = lro_desc->parent;
	int tcp_data_len = TCP_PAYLOAD_LENGTH(iph, tcph);

	lro_add_common(lro_desc, iph, tcph, tcp_data_len);

	skb_pull(skb, (skb->len - tcp_data_len));
	parent->truesize += skb->truesize;

	if (lro_desc->last_skb)
		lro_desc->last_skb->next = skb;
	else
		skb_shinfo(parent)->frag_list = skb;

	lro_desc->last_skb = skb;
}