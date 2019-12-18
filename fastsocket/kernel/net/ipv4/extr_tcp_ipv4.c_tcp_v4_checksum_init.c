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
struct sk_buff {scalar_t__ ip_summed; int len; int /*<<< orphan*/  csum; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  __skb_checksum_complete (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_tcpudp_nofold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_check (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __sum16 tcp_v4_checksum_init(struct sk_buff *skb)
{
	const struct iphdr *iph = ip_hdr(skb);

	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		if (!tcp_v4_check(skb->len, iph->saddr,
				  iph->daddr, skb->csum)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			return 0;
		}
	}

	skb->csum = csum_tcpudp_nofold(iph->saddr, iph->daddr,
				       skb->len, IPPROTO_TCP, 0);

	if (skb->len <= 76) {
		return __skb_checksum_complete(skb);
	}
	return 0;
}