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
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_no_check; int /*<<< orphan*/  sk_protocol; } ;
struct sk_buff {int len; scalar_t__ ip_summed; struct sock* sk; } ;
struct rtable {int /*<<< orphan*/  rt_src; } ;
struct inet_sock {int /*<<< orphan*/  recverr; int /*<<< orphan*/  sport; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int ENOBUFS ; 
 int IS_UDPLITE (struct sock*) ; 
 scalar_t__ UDP_CSUM_NOXMIT ; 
 int /*<<< orphan*/  UDP_INC_STATS_USER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_MIB_OUTDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_SNDBUFERRORS ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip_send_skb (struct sk_buff*) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  udp4_hwcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_csum (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  udplite_csum (struct sk_buff*) ; 

__attribute__((used)) static int udp_send_skb(struct sk_buff *skb, __be32 daddr, __be32 dport)
{
	struct sock *sk = skb->sk;
	struct inet_sock *inet = inet_sk(sk);
	struct udphdr *uh;
	struct rtable *rt = (struct rtable *)skb_dst(skb);
	int err = 0;
	int is_udplite = IS_UDPLITE(sk);
	int offset = skb_transport_offset(skb);
	int len = skb->len - offset;
	__wsum csum = 0;

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = inet->sport;
	uh->dest = dport;
	uh->len = htons(len);
	uh->check = 0;

	if (is_udplite)  				 /*     UDP-Lite      */
		csum = udplite_csum(skb);

	else if (sk->sk_no_check == UDP_CSUM_NOXMIT) {   /* UDP csum disabled */

		skb->ip_summed = CHECKSUM_NONE;
		goto send;

	} else if (skb->ip_summed == CHECKSUM_PARTIAL) { /* UDP hardware csum */

		udp4_hwcsum(skb, rt->rt_src, daddr);
		goto send;

	} else
		csum = udp_csum(skb);

	/* add protocol-dependent pseudo-header */
	uh->check = csum_tcpudp_magic(rt->rt_src, daddr, len,
				      sk->sk_protocol, csum);
	if (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip_send_skb(skb);
	if (err) {
		if (err == -ENOBUFS && !inet->recverr) {
			UDP_INC_STATS_USER(sock_net(sk),
					   UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		}
	} else
		UDP_INC_STATS_USER(sock_net(sk),
				   UDP_MIB_OUTDATAGRAMS, is_udplite);
	return err;
}