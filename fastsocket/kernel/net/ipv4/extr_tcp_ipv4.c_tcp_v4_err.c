#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  seq; int /*<<< orphan*/  source; } ;
struct tcp_sock {int snd_una; int /*<<< orphan*/  srtt; int /*<<< orphan*/  snd_nxt; } ;
struct sock {int sk_state; int sk_err; int sk_err_soft; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;
struct sk_buff {int len; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct request_sock {int /*<<< orphan*/  sk; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet_sock {scalar_t__ recverr; } ;
struct inet_connection_sock {int icsk_backoff; int icsk_rto; int /*<<< orphan*/  icsk_retransmits; } ;
typedef  int __u32 ;
struct TYPE_8__ {scalar_t__ when; } ;
struct TYPE_7__ {int errno; } ;
struct TYPE_6__ {int type; int code; } ;
struct TYPE_5__ {int snt_isn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EHOSTUNREACH ; 
 int EPROTO ; 
#define  ICMP_DEST_UNREACH 134 
 int const ICMP_FRAG_NEEDED ; 
 int const ICMP_HOST_UNREACH ; 
 int /*<<< orphan*/  ICMP_INC_STATS_BH (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int const ICMP_NET_UNREACH ; 
#define  ICMP_PARAMETERPROB 133 
#define  ICMP_SOURCE_QUENCH 132 
#define  ICMP_TIME_EXCEEDED 131 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  LINUX_MIB_LOCKDROPPEDICMPS ; 
 int /*<<< orphan*/  LINUX_MIB_OUTOFWINDOWICMPS ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (struct net*,int /*<<< orphan*/ ) ; 
 int const NR_ICMP_UNREACH ; 
 int TCP_CLOSE ; 
#define  TCP_LISTEN 130 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 TYPE_4__* TCP_SKB_CB (struct sk_buff*) ; 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 int TCP_TIMEOUT_INIT ; 
 int TCP_TIME_WAIT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __tcp_set_rto (struct tcp_sock*) ; 
 int /*<<< orphan*/  between (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_pmtu_discovery (struct sock*,struct iphdr*,int /*<<< orphan*/ ) ; 
 TYPE_3__* icmp_err_convert ; 
 TYPE_2__* icmp_hdr (struct sk_buff*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (struct sock*,struct request_sock*,struct request_sock**) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct request_sock* inet_csk_search_req (struct sock*,struct request_sock***,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct sock* inet_lookup (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 int min (int,scalar_t__) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  tcp_bound_rto (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 int /*<<< orphan*/  tcp_retransmit_timer (struct sock*) ; 
 TYPE_1__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_time_stamp ; 
 struct sk_buff* tcp_write_queue_head (struct sock*) ; 

void tcp_v4_err(struct sk_buff *icmp_skb, u32 info)
{
	struct iphdr *iph = (struct iphdr *)icmp_skb->data;
	struct tcphdr *th = (struct tcphdr *)(icmp_skb->data + (iph->ihl << 2));
	struct inet_connection_sock *icsk;
	struct tcp_sock *tp;
	struct inet_sock *inet;
	const int type = icmp_hdr(icmp_skb)->type;
	const int code = icmp_hdr(icmp_skb)->code;
	struct sock *sk;
	struct sk_buff *skb;
	__u32 seq;
	__u32 remaining;
	int err;
	struct net *net = dev_net(icmp_skb->dev);

	if (icmp_skb->len < (iph->ihl << 2) + 8) {
		ICMP_INC_STATS_BH(net, ICMP_MIB_INERRORS);
		return;
	}

	sk = inet_lookup(net, &tcp_hashinfo, iph->daddr, th->dest,
			iph->saddr, th->source, inet_iif(icmp_skb));
	if (!sk) {
		ICMP_INC_STATS_BH(net, ICMP_MIB_INERRORS);
		return;
	}
	if (sk->sk_state == TCP_TIME_WAIT) {
		inet_twsk_put(inet_twsk(sk));
		return;
	}

	bh_lock_sock(sk);
	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved differently.
	 */
	if (sock_owned_by_user(sk))
		NET_INC_STATS_BH(net, LINUX_MIB_LOCKDROPPEDICMPS);

	if (sk->sk_state == TCP_CLOSE)
		goto out;

	icsk = inet_csk(sk);
	tp = tcp_sk(sk);
	seq = ntohl(th->seq);
	if (sk->sk_state != TCP_LISTEN &&
	    !between(seq, tp->snd_una, tp->snd_nxt)) {
		NET_INC_STATS_BH(net, LINUX_MIB_OUTOFWINDOWICMPS);
		goto out;
	}

	switch (type) {
	case ICMP_SOURCE_QUENCH:
		/* Just silently ignore these. */
		goto out;
	case ICMP_PARAMETERPROB:
		err = EPROTO;
		break;
	case ICMP_DEST_UNREACH:
		if (code > NR_ICMP_UNREACH)
			goto out;

		if (code == ICMP_FRAG_NEEDED) { /* PMTU discovery (RFC1191) */
			if (!sock_owned_by_user(sk))
				do_pmtu_discovery(sk, iph, info);
			goto out;
		}

		err = icmp_err_convert[code].errno;
		/* check if icmp_skb allows revert of backoff
		 * (see draft-zimmermann-tcp-lcd) */
		if (code != ICMP_NET_UNREACH && code != ICMP_HOST_UNREACH)
			break;
		if (seq != tp->snd_una  || !icsk->icsk_retransmits ||
		    !icsk->icsk_backoff)
			break;

		if (sock_owned_by_user(sk))
			break;

		icsk->icsk_backoff--;
		inet_csk(sk)->icsk_rto = (tp->srtt ? __tcp_set_rto(tp) :
			TCP_TIMEOUT_INIT) << icsk->icsk_backoff;
		tcp_bound_rto(sk);

		skb = tcp_write_queue_head(sk);
		BUG_ON(!skb);

		remaining = icsk->icsk_rto - min(icsk->icsk_rto,
				tcp_time_stamp - TCP_SKB_CB(skb)->when);

		if (remaining) {
			inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
						  remaining, TCP_RTO_MAX);
		} else {
			/* RTO revert clocked out retransmission.
			 * Will retransmit now */
			tcp_retransmit_timer(sk);
		}

		break;
	case ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		break;
	default:
		goto out;
	}

	switch (sk->sk_state) {
		struct request_sock *req, **prev;
	case TCP_LISTEN:
		if (sock_owned_by_user(sk))
			goto out;

		req = inet_csk_search_req(sk, &prev, th->dest,
					  iph->daddr, iph->saddr);
		if (!req)
			goto out;

		/* ICMPs are not backlogged, hence we cannot get
		   an established socket here.
		 */
		WARN_ON(req->sk);

		if (seq != tcp_rsk(req)->snt_isn) {
			NET_INC_STATS_BH(net, LINUX_MIB_OUTOFWINDOWICMPS);
			goto out;
		}

		/*
		 * Still in SYN_RECV, just remove it silently.
		 * There is no good way to pass the error to the newly
		 * created socket, and POSIX does not want network
		 * errors returned from accept().
		 */
		inet_csk_reqsk_queue_drop(sk, req, prev);
		goto out;

	case TCP_SYN_SENT:
	case TCP_SYN_RECV:  /* Cannot happen.
			       It can f.e. if SYNs crossed.
			     */
		if (!sock_owned_by_user(sk)) {
			sk->sk_err = err;

			sk->sk_error_report(sk);

			tcp_done(sk);
		} else {
			sk->sk_err_soft = err;
		}
		goto out;
	}

	/* If we've already connected we will keep trying
	 * until we time out, or the user gives up.
	 *
	 * rfc1122 4.2.3.9 allows to consider as hard errors
	 * only PROTO_UNREACH and PORT_UNREACH (well, FRAG_FAILED too,
	 * but it is obsoleted by pmtu discovery).
	 *
	 * Note, that in modern internet, where routing is unreliable
	 * and in each dark corner broken firewalls sit, sending random
	 * errors ordered by their masters even this two messages finally lose
	 * their original sense (even Linux sends invalid PORT_UNREACHs)
	 *
	 * Now we are in compliance with RFCs.
	 *							--ANK (980905)
	 */

	inet = inet_sk(sk);
	if (!sock_owned_by_user(sk) && inet->recverr) {
		sk->sk_err = err;
		sk->sk_error_report(sk);
	} else	{ /* Only an error on timeout */
		sk->sk_err_soft = err;
	}

out:
	bh_unlock_sock(sk);
	sock_put(sk);
}