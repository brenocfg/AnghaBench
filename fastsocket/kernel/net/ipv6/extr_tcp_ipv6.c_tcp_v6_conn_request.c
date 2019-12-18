#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  user_mss; } ;
struct tcp_sock {TYPE_1__ rx_opt; } ;
struct tcp_options_received {int mss_clamp; scalar_t__ tstamp_ok; scalar_t__ saw_tstamp; int /*<<< orphan*/  user_mss; } ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  users; } ;
struct request_sock {scalar_t__ cookie_ts; int /*<<< orphan*/  mss; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_8__ {scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_9__ {TYPE_2__ bits; } ;
struct ipv6_pinfo {TYPE_3__ rxopt; } ;
struct inet6_request_sock {struct sk_buff* pktopts; int /*<<< orphan*/  iif; int /*<<< orphan*/  rmt_addr; int /*<<< orphan*/  loc_addr; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_12__ {scalar_t__ when; } ;
struct TYPE_11__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  snt_synack; scalar_t__ snt_isn; int /*<<< orphan*/ * af_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_MIN_MTU ; 
 int /*<<< orphan*/  TCP_ECN_create_request (struct request_sock*,int /*<<< orphan*/ ) ; 
 TYPE_6__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cookie_v6_init_sequence (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_csk_reqsk_queue_hash_add (struct sock*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct request_sock* inet6_reqsk_alloc (int /*<<< orphan*/ *) ; 
 struct inet6_request_sock* inet6_rsk (struct request_sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ inet_csk_reqsk_queue_is_full (struct sock*) ; 
 int inet_csk_reqsk_queue_young (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  reqsk_free (struct request_sock*) ; 
 int /*<<< orphan*/  security_inet_conn_request (struct sock*,struct sk_buff*,struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  syn_flood_warning (struct sk_buff*) ; 
 scalar_t__ sysctl_tcp_syncookies ; 
 int /*<<< orphan*/  tcp6_request_sock_ops ; 
 int /*<<< orphan*/  tcp_clear_options (struct tcp_options_received*) ; 
 int /*<<< orphan*/  tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_openreq_init (struct request_sock*,struct tcp_options_received*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_parse_options (struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_request_sock_ipv6_ops ; 
 TYPE_4__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 
 int tcp_v4_conn_request (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_v6_init_sequence (struct sk_buff*) ; 
 scalar_t__ tcp_v6_send_synack (struct sock*,struct request_sock*) ; 

__attribute__((used)) static int tcp_v6_conn_request(struct sock *sk, struct sk_buff *skb)
{
	struct inet6_request_sock *treq;
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct tcp_options_received tmp_opt;
	struct tcp_sock *tp = tcp_sk(sk);
	struct request_sock *req = NULL;
	__u32 isn = TCP_SKB_CB(skb)->when;
#ifdef CONFIG_SYN_COOKIES
	int want_cookie = 0;
#else
#define want_cookie 0
#endif

	if (skb->protocol == htons(ETH_P_IP))
		return tcp_v4_conn_request(sk, skb);

	if (!ipv6_unicast_destination(skb))
		goto drop;

	if (inet_csk_reqsk_queue_is_full(sk) && !isn) {
		if (net_ratelimit())
			syn_flood_warning(skb);
#ifdef CONFIG_SYN_COOKIES
		if (sysctl_tcp_syncookies)
			want_cookie = 1;
		else
#endif
		goto drop;
	}

	if (sk_acceptq_is_full(sk) && inet_csk_reqsk_queue_young(sk) > 1)
		goto drop;

	req = inet6_reqsk_alloc(&tcp6_request_sock_ops);
	if (req == NULL)
		goto drop;

#ifdef CONFIG_TCP_MD5SIG
	tcp_rsk(req)->af_specific = &tcp_request_sock_ipv6_ops;
#endif

	tcp_clear_options(&tmp_opt);
	tmp_opt.mss_clamp = IPV6_MIN_MTU - sizeof(struct tcphdr) - sizeof(struct ipv6hdr);
	tmp_opt.user_mss = tp->rx_opt.user_mss;

	tcp_parse_options(skb, &tmp_opt, 0);

	if (want_cookie && !tmp_opt.saw_tstamp)
		tcp_clear_options(&tmp_opt);

	tmp_opt.tstamp_ok = tmp_opt.saw_tstamp;
	tcp_openreq_init(req, &tmp_opt, skb);

	treq = inet6_rsk(req);
	ipv6_addr_copy(&treq->rmt_addr, &ipv6_hdr(skb)->saddr);
	ipv6_addr_copy(&treq->loc_addr, &ipv6_hdr(skb)->daddr);
	if (!want_cookie)
		TCP_ECN_create_request(req, tcp_hdr(skb));

	treq->iif = sk->sk_bound_dev_if;

	/* So that link locals have meaning */
	if (!sk->sk_bound_dev_if &&
	    ipv6_addr_type(&treq->rmt_addr) & IPV6_ADDR_LINKLOCAL)
		treq->iif = inet6_iif(skb);

	if (want_cookie) {
		isn = cookie_v6_init_sequence(sk, skb, &req->mss);
		req->cookie_ts = tmp_opt.tstamp_ok;
	} else if (!isn) {
		if (ipv6_opt_accepted(sk, skb) ||
		    np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo ||
		    np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim) {
			atomic_inc(&skb->users);
			treq->pktopts = skb;
		}

		isn = tcp_v6_init_sequence(skb);
	}

	tcp_rsk(req)->snt_isn = isn;
	tcp_rsk(req)->snt_synack = tcp_time_stamp;

	security_inet_conn_request(sk, skb, req);

	if (tcp_v6_send_synack(sk, req))
		goto drop;

	if (!want_cookie) {
		inet6_csk_reqsk_queue_hash_add(sk, req, TCP_TIMEOUT_INIT);
		return 0;
	}

drop:
	if (req)
		reqsk_free(req);

	return 0; /* don't send reset */
}