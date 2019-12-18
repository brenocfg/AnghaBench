#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ user_mss; } ;
struct tcp_sock {int write_seq; scalar_t__ advmss; int /*<<< orphan*/  total_retrans; TYPE_1__ rx_opt; } ;
struct tcp_md5sig_key {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
struct sock {int /*<<< orphan*/  sk_route_caps; int /*<<< orphan*/  sk_gso_type; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  retrans; } ;
struct ip_options {scalar_t__ optlen; } ;
struct inet_sock {int id; int /*<<< orphan*/  daddr; int /*<<< orphan*/  mc_ttl; int /*<<< orphan*/  mc_index; int /*<<< orphan*/  opt; int /*<<< orphan*/  saddr; int /*<<< orphan*/  rcv_saddr; } ;
struct inet_request_sock {struct ip_options* opt; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rmt_addr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_10__ {scalar_t__ icsk_ext_hdr_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; } ;
struct TYPE_8__ {int /*<<< orphan*/  rcv_tos; } ;
struct TYPE_7__ {scalar_t__ snt_synack; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENDROPS ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 int /*<<< orphan*/  NETIF_F_GSO_MASK ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 int /*<<< orphan*/  __inet_hash_nolisten (struct sock*) ; 
 scalar_t__ __inet_inherit_port (struct sock*,struct sock*) ; 
 scalar_t__ dst_metric (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 TYPE_5__* inet_csk (struct sock*) ; 
 struct dst_entry* inet_csk_route_req (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int jiffies ; 
 char* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ip_options*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 TYPE_3__* sk_extended (struct sock*) ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* tcp_create_openreq_child (struct sock*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_initialize_rcv_mss (struct sock*) ; 
 int /*<<< orphan*/  tcp_mtup_init (struct sock*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_time_stamp ; 
 int /*<<< orphan*/  tcp_v4_md5_do_add (struct sock*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct tcp_md5sig_key* tcp_v4_md5_do_lookup (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_valid_rtt_meas (struct sock*,scalar_t__) ; 

struct sock *tcp_v4_syn_recv_sock(struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req,
				  struct dst_entry *dst)
{
	struct inet_request_sock *ireq;
	struct inet_sock *newinet;
	struct tcp_sock *newtp;
	struct sock *newsk;
#ifdef CONFIG_TCP_MD5SIG
	struct tcp_md5sig_key *key;
#endif
	struct ip_options *inet_opt;

	if (sk_acceptq_is_full(sk))
		goto exit_overflow;

	if (!dst && (dst = inet_csk_route_req(sk, req)) == NULL)
		goto exit;

	newsk = tcp_create_openreq_child(sk, req, skb);
	if (!newsk)
		goto exit_nonewsk;

	newsk->sk_gso_type = SKB_GSO_TCPV4;
	sk_setup_caps(newsk, dst);

	newtp		      = tcp_sk(newsk);
	newinet		      = inet_sk(newsk);
	ireq		      = inet_rsk(req);
	newinet->daddr	      = ireq->rmt_addr;
	newinet->rcv_saddr    = ireq->loc_addr;
	newinet->saddr	      = ireq->loc_addr;
	inet_opt	      = ireq->opt;
	rcu_assign_pointer(newinet->opt, inet_opt);
	ireq->opt	      = NULL;
	newinet->mc_index     = inet_iif(skb);
	newinet->mc_ttl	      = ip_hdr(skb)->ttl;
	sk_extended(newsk)->rcv_tos = ip_hdr(skb)->tos;
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	if (inet_opt)
		inet_csk(newsk)->icsk_ext_hdr_len = inet_opt->optlen;
	newinet->id = newtp->write_seq ^ jiffies;

	tcp_mtup_init(newsk);
	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = dst_metric(dst, RTAX_ADVMSS);
	if (tcp_sk(sk)->rx_opt.user_mss &&
	    tcp_sk(sk)->rx_opt.user_mss < newtp->advmss)
		newtp->advmss = tcp_sk(sk)->rx_opt.user_mss;

	tcp_initialize_rcv_mss(newsk);
	if (tcp_rsk(req)->snt_synack)
		tcp_valid_rtt_meas(newsk,
		    tcp_time_stamp - tcp_rsk(req)->snt_synack);
	newtp->total_retrans = req->retrans;

#ifdef CONFIG_TCP_MD5SIG
	/* Copy over the MD5 key from the original socket */
	if ((key = tcp_v4_md5_do_lookup(sk, newinet->daddr)) != NULL) {
		/*
		 * We're using one, so create a matching key
		 * on the newsk structure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		char *newkey = kmemdup(key->key, key->keylen, GFP_ATOMIC);
		if (newkey != NULL)
			tcp_v4_md5_do_add(newsk, newinet->daddr,
					  newkey, key->keylen);
		newsk->sk_route_caps &= ~NETIF_F_GSO_MASK;
	}
#endif

	if (__inet_inherit_port(sk, newsk) < 0) {
		sock_put(newsk);
		goto exit;
	}
	__inet_hash_nolisten(newsk);

	return newsk;

exit_overflow:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
exit_nonewsk:
	dst_release(dst);
exit:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENDROPS);
	return NULL;
}