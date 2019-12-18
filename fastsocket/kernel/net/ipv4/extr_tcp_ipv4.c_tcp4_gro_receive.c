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
struct sk_buff {int ip_summed; int /*<<< orphan*/  csum; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;
struct TYPE_2__ {int flush; } ;

/* Variables and functions */
#define  CHECKSUM_COMPLETE 129 
#define  CHECKSUM_NONE 128 
 void* CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_tcpudp_nofold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_gro_len (struct sk_buff*) ; 
 struct iphdr* skb_gro_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_offset (struct sk_buff*) ; 
 struct sk_buff** tcp_gro_receive (struct sk_buff**,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sk_buff **tcp4_gro_receive(struct sk_buff **head, struct sk_buff *skb)
{
	struct iphdr *iph = skb_gro_network_header(skb);
	__wsum wsum;
	__sum16 sum;

	switch (skb->ip_summed) {
	case CHECKSUM_COMPLETE:
		if (!tcp_v4_check(skb_gro_len(skb), iph->saddr, iph->daddr,
				  skb->csum)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			break;
		}
flush:
		NAPI_GRO_CB(skb)->flush = 1;
		return NULL;

	case CHECKSUM_NONE:
		wsum = csum_tcpudp_nofold(iph->saddr, iph->daddr,
					  skb_gro_len(skb), IPPROTO_TCP, 0);
		sum = csum_fold(skb_checksum(skb,
					     skb_gro_offset(skb),
					     skb_gro_len(skb),
					     wsum));
		if (sum)
			goto flush;

		skb->ip_summed = CHECKSUM_UNNECESSARY;
		break;
	}

	return tcp_gro_receive(head, skb);
}