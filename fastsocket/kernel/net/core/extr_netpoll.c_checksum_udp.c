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
struct udphdr {scalar_t__ check; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  __skb_checksum_complete (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_tcpudp_nofold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 

__attribute__((used)) static __sum16 checksum_udp(struct sk_buff *skb, struct udphdr *uh,
			    unsigned short ulen, __be32 saddr, __be32 daddr)
{
	__wsum psum;

	if (uh->check == 0 || skb_csum_unnecessary(skb))
		return 0;

	psum = csum_tcpudp_nofold(saddr, daddr, ulen, IPPROTO_UDP, 0);

	if (skb->ip_summed == CHECKSUM_COMPLETE &&
	    !csum_fold(csum_add(psum, skb->csum)))
		return 0;

	skb->csum = psum;

	return __skb_checksum_complete(skb);
}