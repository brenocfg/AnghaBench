#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  seq; int /*<<< orphan*/  source; } ;
struct tcp_sock {int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  snd_una; } ;
struct sock {int sk_state; int sk_err_soft; int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {TYPE_4__* dev; scalar_t__ data; } ;
struct request_sock {int /*<<< orphan*/ * sk; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ipv6_pinfo {scalar_t__ recverr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  dst_cookie; } ;
struct inet_sock {int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; } ;
struct inet6_skb_parm {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  oif; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_9__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_8__ {scalar_t__ icsk_pmtu_cookie; } ;
struct TYPE_7__ {scalar_t__ hop_limit; } ;
struct TYPE_6__ {int /*<<< orphan*/  snt_isn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_INC_STATS_BH (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_MIB_INERRORS ; 
 scalar_t__ ICMPV6_PKT_TOOBIG ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LINUX_MIB_LOCKDROPPEDICMPS ; 
 int /*<<< orphan*/  LINUX_MIB_OUTOFWINDOWICMPS ; 
 int /*<<< orphan*/  LINUX_MIB_TCPMINTTLDROP ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (struct net*,int /*<<< orphan*/ ) ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int TCP_CLOSE ; 
#define  TCP_LISTEN 130 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 int TCP_TIME_WAIT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __in6_dev_get (TYPE_4__*) ; 
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  between (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct net* dev_net (TYPE_4__*) ; 
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  icmpv6_err_convert (scalar_t__,scalar_t__,int*) ; 
 struct request_sock* inet6_csk_search_req (struct sock*,struct request_sock***,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct sock* inet6_lookup (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (struct sock*,struct request_sock*,struct request_sock**) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 int ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_skb_classify_flow (struct sk_buff*,struct flowi*) ; 
 scalar_t__ sk_get_min_hopcount (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 TYPE_1__* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_simple_retransmit (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,scalar_t__) ; 
 int xfrm_lookup (struct net*,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
		u8 type, u8 code, int offset, __be32 info)
{
	struct ipv6hdr *hdr = (struct ipv6hdr*)skb->data;
	const struct tcphdr *th = (struct tcphdr *)(skb->data+offset);
	struct ipv6_pinfo *np;
	struct sock *sk;
	int err;
	struct tcp_sock *tp;
	__u32 seq;
	struct net *net = dev_net(skb->dev);

	sk = inet6_lookup(net, &tcp_hashinfo, &hdr->daddr,
			th->dest, &hdr->saddr, th->source, skb->dev->ifindex);

	if (sk == NULL) {
		ICMP6_INC_STATS_BH(net, __in6_dev_get(skb->dev),
				   ICMP6_MIB_INERRORS);
		return;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		inet_twsk_put(inet_twsk(sk));
		return;
	}

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk))
		NET_INC_STATS_BH(net, LINUX_MIB_LOCKDROPPEDICMPS);

	if (sk->sk_state == TCP_CLOSE)
		goto out;

	if (ipv6_hdr(skb)->hop_limit < sk_get_min_hopcount(sk)) {
		NET_INC_STATS_BH(net, LINUX_MIB_TCPMINTTLDROP);
		goto out;
	}

	tp = tcp_sk(sk);
	seq = ntohl(th->seq);
	if (sk->sk_state != TCP_LISTEN &&
	    !between(seq, tp->snd_una, tp->snd_nxt)) {
		NET_INC_STATS_BH(net, LINUX_MIB_OUTOFWINDOWICMPS);
		goto out;
	}

	np = inet6_sk(sk);

	if (type == ICMPV6_PKT_TOOBIG) {
		struct dst_entry *dst = NULL;

		if (sock_owned_by_user(sk))
			goto out;
		if ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE))
			goto out;

		/* icmp should have updated the destination cache entry */
		dst = __sk_dst_check(sk, np->dst_cookie);

		if (dst == NULL) {
			struct inet_sock *inet = inet_sk(sk);
			struct flowi fl;

			/* BUGGG_FUTURE: Again, it is not clear how
			   to handle rthdr case. Ignore this complexity
			   for now.
			 */
			memset(&fl, 0, sizeof(fl));
			fl.proto = IPPROTO_TCP;
			ipv6_addr_copy(&fl.fl6_dst, &np->daddr);
			ipv6_addr_copy(&fl.fl6_src, &np->saddr);
			fl.oif = sk->sk_bound_dev_if;
			fl.fl_ip_dport = inet->dport;
			fl.fl_ip_sport = inet->sport;
			security_skb_classify_flow(skb, &fl);

			if ((err = ip6_dst_lookup(sk, &dst, &fl))) {
				sk->sk_err_soft = -err;
				goto out;
			}

			if ((err = xfrm_lookup(net, &dst, &fl, sk, 0)) < 0) {
				sk->sk_err_soft = -err;
				goto out;
			}

		} else
			dst_hold(dst);

		if (inet_csk(sk)->icsk_pmtu_cookie > dst_mtu(dst)) {
			tcp_sync_mss(sk, dst_mtu(dst));
			tcp_simple_retransmit(sk);
		} /* else let the usual retransmit timer handle it */
		dst_release(dst);
		goto out;
	}

	icmpv6_err_convert(type, code, &err);

	/* Might be for an request_sock */
	switch (sk->sk_state) {
		struct request_sock *req, **prev;
	case TCP_LISTEN:
		if (sock_owned_by_user(sk))
			goto out;

		req = inet6_csk_search_req(sk, &prev, th->dest, &hdr->daddr,
					   &hdr->saddr, inet6_iif(skb));
		if (!req)
			goto out;

		/* ICMPs are not backlogged, hence we cannot get
		 * an established socket here.
		 */
		WARN_ON(req->sk != NULL);

		if (seq != tcp_rsk(req)->snt_isn) {
			NET_INC_STATS_BH(net, LINUX_MIB_OUTOFWINDOWICMPS);
			goto out;
		}

		inet_csk_reqsk_queue_drop(sk, req, prev);
		goto out;

	case TCP_SYN_SENT:
	case TCP_SYN_RECV:  /* Cannot happen.
			       It can, it SYNs are crossed. --ANK */
		if (!sock_owned_by_user(sk)) {
			sk->sk_err = err;
			sk->sk_error_report(sk);		/* Wake people up to see the error (see connect in sock.c) */

			tcp_done(sk);
		} else
			sk->sk_err_soft = err;
		goto out;
	}

	if (!sock_owned_by_user(sk) && np->recverr) {
		sk->sk_err = err;
		sk->sk_error_report(sk);
	} else
		sk->sk_err_soft = err;

out:
	bh_unlock_sock(sk);
	sock_put(sk);
}