#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {scalar_t__ rcv_nxt; } ;
struct sock {int sk_state; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ len; int /*<<< orphan*/  rxhash; } ;
struct TYPE_7__ {scalar_t__ rxtclass; scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_8__ {TYPE_1__ bits; scalar_t__ all; } ;
struct ipv6_pinfo {int /*<<< orphan*/  pktoptions; TYPE_2__ rxopt; int /*<<< orphan*/  mcast_hops; int /*<<< orphan*/  mcast_oif; } ;
struct TYPE_11__ {scalar_t__ end_seq; } ;
struct TYPE_10__ {int /*<<< orphan*/  hop_limit; } ;
struct TYPE_9__ {int /*<<< orphan*/  rcv_tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int /*<<< orphan*/  TCP_CHECK_TIMER (struct sock*) ; 
 int TCP_ESTABLISHED ; 
 int /*<<< orphan*/  TCP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 TYPE_6__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_tclass (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_3__* sk_extended (struct sock*) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_checksum_complete (struct sk_buff*) ; 
 scalar_t__ tcp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ tcp_rcv_established (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tcp_rcv_state_process (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_v4_do_rcv (struct sock*,struct sk_buff*) ; 
 struct sock* tcp_v6_hnd_req (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_v6_inbound_md5_hash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_send_reset (struct sock*,struct sk_buff*) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int tcp_v6_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct tcp_sock *tp;
	struct sk_buff *opt_skb = NULL;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, tcp_rcv_established and rcv_established
	   handle them correctly, but it is not case with
	   tcp_v6_hnd_req and tcp_v6_send_reset().   --ANK
	 */

	if (skb->protocol == htons(ETH_P_IP))
		return tcp_v4_do_rcv(sk, skb);

#ifdef CONFIG_TCP_MD5SIG
	if (tcp_v6_inbound_md5_hash (sk, skb))
		goto discard;
#endif

	if (sk_filter(sk, skb))
		goto discard;

	/*
	 *	socket locking is here for SMP purposes as backlog rcv
	 *	is currently called with bh processing disabled.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the only place in our code, where we
	   may make it not affecting IPv4.
	   The rest of code is protocol independent,
	   and I do not like idea to uglify IPv4.

	   Actually, all the idea behind IPV6_PKTOPTIONS
	   looks not very well thought. For now we latch
	   options, received in the last packet, enqueued
	   by tcp. Feel free to propose better solution.
					       --ANK (980728)
	 */
	if (np->rxopt.all)
		opt_skb = skb_clone(skb, GFP_ATOMIC);

	if (sk->sk_state == TCP_ESTABLISHED) { /* Fast path */
		TCP_CHECK_TIMER(sk);
		sock_rps_save_rxhash(sk, skb->rxhash);
		if (tcp_rcv_established(sk, skb, tcp_hdr(skb), skb->len))
			goto reset;
		TCP_CHECK_TIMER(sk);
		if (opt_skb)
			goto ipv6_pktoptions;
		return 0;
	}

	if (skb->len < tcp_hdrlen(skb) || tcp_checksum_complete(skb))
		goto csum_err;

	if (sk->sk_state == TCP_LISTEN) {
		struct sock *nsk = tcp_v6_hnd_req(sk, skb);
		if (!nsk)
			goto discard;

		/*
		 * Queue it on the new socket if the new socket is active,
		 * otherwise we just shortcircuit this and continue with
		 * the new socket..
		 */
		if(nsk != sk) {
			sock_rps_save_rxhash(nsk, skb->rxhash);
			if (tcp_child_process(sk, nsk, skb))
				goto reset;
			if (opt_skb)
				__kfree_skb(opt_skb);
			return 0;
		}
	} else
		sock_rps_save_rxhash(sk, skb->rxhash);

	TCP_CHECK_TIMER(sk);
	if (tcp_rcv_state_process(sk, skb, tcp_hdr(skb), skb->len))
		goto reset;
	TCP_CHECK_TIMER(sk);
	if (opt_skb)
		goto ipv6_pktoptions;
	return 0;

reset:
	tcp_v6_send_reset(sk, skb);
discard:
	if (opt_skb)
		__kfree_skb(opt_skb);
	kfree_skb(skb);
	return 0;
csum_err:
	TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_INERRS);
	goto discard;


ipv6_pktoptions:
	/* Do you ask, what is it?

	   1. skb was enqueued by tcp.
	   2. skb is added to tail of read queue, rather than out of order.
	   3. socket is not in passive state.
	   4. Finally, it really contains options, which user wants to receive.
	 */
	tp = tcp_sk(sk);
	if (TCP_SKB_CB(opt_skb)->end_seq == tp->rcv_nxt &&
	    !((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))) {
		if (np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo)
			np->mcast_oif = inet6_iif(opt_skb);
		if (np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim)
			np->mcast_hops = ipv6_hdr(opt_skb)->hop_limit;
		if (np->rxopt.bits.rxtclass)
			sk_extended(sk)->rcv_tos = ipv6_tclass(ipv6_hdr(skb));
		if (ipv6_opt_accepted(sk, opt_skb)) {
			skb_set_owner_r(opt_skb, sk);
			opt_skb = xchg(&np->pktoptions, opt_skb);
		} else {
			__kfree_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, NULL);
		}
	}

	kfree_skb(opt_skb);
	return 0;
}