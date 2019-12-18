#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct udp_sock {scalar_t__ pending; scalar_t__ len; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct flowi {int /*<<< orphan*/  proto; int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  fl_ip_sport; } ;
struct TYPE_3__ {struct flowi fl; } ;
struct inet_sock {TYPE_1__ cork; } ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_4__ {int /*<<< orphan*/  recverr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int ENOBUFS ; 
 int IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  UDP6_INC_STATS_USER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_MIB_OUTDATAGRAMS ; 
 int /*<<< orphan*/  UDP_MIB_SNDBUFERRORS ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip6_push_pending_frames (struct sock*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  udp6_hwcsum_outgoing (struct sock*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  udp_csum_outgoing (struct sock*,struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 
 int udp_push_pending_frames (struct sock*) ; 
 struct udp_sock* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udplite_csum_outgoing (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int udp_v6_push_pending_frames(struct sock *sk)
{
	struct sk_buff *skb;
	struct udphdr *uh;
	struct udp_sock  *up = udp_sk(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct flowi *fl;
	int err = 0;
	int is_udplite = IS_UDPLITE(sk);
	__wsum csum = 0;

	if (up->pending == AF_INET)
		return udp_push_pending_frames(sk);

	fl = &inet->cork.fl;

	/* Grab the skbuff where UDP header space exists. */
	if ((skb = skb_peek(&sk->sk_write_queue)) == NULL)
		goto out;

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = fl->fl_ip_sport;
	uh->dest = fl->fl_ip_dport;
	uh->len = htons(up->len);
	uh->check = 0;

	if (is_udplite)
		csum = udplite_csum_outgoing(sk, skb);
	else if (skb->ip_summed == CHECKSUM_PARTIAL) { /* UDP hardware csum */
		udp6_hwcsum_outgoing(sk, skb, &fl->fl6_src, &fl->fl6_dst,
				     up->len);
		goto send;
	} else
		csum = udp_csum_outgoing(sk, skb);

	/* add protocol-dependent pseudo-header */
	uh->check = csum_ipv6_magic(&fl->fl6_src, &fl->fl6_dst,
				    up->len, fl->proto, csum   );
	if (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip6_push_pending_frames(sk);
	if (err) {
		if (err == -ENOBUFS && !inet6_sk(sk)->recverr) {
			UDP6_INC_STATS_USER(sock_net(sk),
					    UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		}
	} else
		UDP6_INC_STATS_USER(sock_net(sk),
				    UDP_MIB_OUTDATAGRAMS, is_udplite);
out:
	up->len = 0;
	up->pending = 0;
	return err;
}