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
struct skb_frag_struct {int page_offset; int size; } ;
struct sk_buff {int truesize; } ;
struct net_lro_desc {struct skb_frag_struct* next_frag; struct sk_buff* parent; } ;
struct iphdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int TCP_PAYLOAD_LENGTH (struct iphdr*,struct tcphdr*) ; 
 int /*<<< orphan*/  lro_add_common (struct net_lro_desc*,struct iphdr*,struct tcphdr*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void lro_add_frags(struct net_lro_desc *lro_desc,
			  int len, int hlen, int truesize,
			  struct skb_frag_struct *skb_frags,
			  struct iphdr *iph, struct tcphdr *tcph)
{
	struct sk_buff *skb = lro_desc->parent;
	int tcp_data_len = TCP_PAYLOAD_LENGTH(iph, tcph);

	lro_add_common(lro_desc, iph, tcph, tcp_data_len);

	skb->truesize += truesize;

	skb_frags[0].page_offset += hlen;
	skb_frags[0].size -= hlen;

	while (tcp_data_len > 0) {
		*(lro_desc->next_frag) = *skb_frags;
		tcp_data_len -= skb_frags->size;
		lro_desc->next_frag++;
		skb_frags++;
		skb_shinfo(skb)->nr_frags++;
	}
}