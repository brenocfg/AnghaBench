#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {int /*<<< orphan*/  total_retrans; int /*<<< orphan*/  advmss; int /*<<< orphan*/ * af_specific; } ;
struct tcp_md5sig_key {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
struct tcp6_sock {int /*<<< orphan*/  inet6; } ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_gso_type; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct request_sock {int /*<<< orphan*/  retrans; } ;
struct ipv6_txoptions {int /*<<< orphan*/  tot_len; scalar_t__ opt_flen; scalar_t__ opt_nflen; scalar_t__ srcrt; } ;
struct in6_addr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  all; } ;
struct ipv6_pinfo {struct ipv6_txoptions* opt; struct in6_addr daddr; int /*<<< orphan*/  mcast_hops; void* mcast_oif; int /*<<< orphan*/ * pktoptions; TYPE_1__ rxopt; int /*<<< orphan*/ * ipv6_fl_list; struct in6_addr rcv_saddr; struct in6_addr saddr; } ;
struct inet_sock {int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/ * opt; int /*<<< orphan*/ * pinet6; } ;
struct inet6_request_sock {int /*<<< orphan*/ * pktopts; int /*<<< orphan*/  iif; struct in6_addr loc_addr; struct in6_addr rmt_addr; } ;
struct flowi {struct in6_addr fl6_dst; int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  oif; struct in6_addr fl6_src; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_13__ {scalar_t__ icsk_ext_hdr_len; int /*<<< orphan*/  icsk_pmtu_cookie; int /*<<< orphan*/ * icsk_af_ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rmt_port; } ;
struct TYPE_11__ {int /*<<< orphan*/  hop_limit; } ;
struct TYPE_10__ {void* rcv_tos; } ;
struct TYPE_9__ {scalar_t__ snt_synack; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENDROPS ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 int /*<<< orphan*/  LOOPBACK4_IPV6 ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int /*<<< orphan*/  SKB_GSO_TCPV6 ; 
 int /*<<< orphan*/  __inet6_hash (struct sock*) ; 
 scalar_t__ __inet_inherit_port (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  __ip6_dst_store (struct sock*,struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_metric (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 void* inet6_iif (struct sk_buff*) ; 
 struct inet6_request_sock* inet6_rsk (struct request_sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_7__* inet_csk (struct sock*) ; 
 TYPE_6__* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_set (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6_txoptions* ipv6_dup_options (struct sock*,struct ipv6_txoptions*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_mapped ; 
 void* ipv6_tclass (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 char* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ipv6_pinfo*,struct ipv6_pinfo*,int) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock*,struct flowi*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 TYPE_3__* sk_extended (struct sock*) ; 
 int /*<<< orphan*/ * skb_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_txoptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* tcp_create_openreq_child (struct sock*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_initialize_rcv_mss (struct sock*) ; 
 int /*<<< orphan*/  tcp_mtup_init (struct sock*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sock_ipv6_mapped_specific ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_time_stamp ; 
 int /*<<< orphan*/  tcp_v4_do_rcv ; 
 struct sock* tcp_v4_syn_recv_sock (struct sock*,struct sk_buff*,struct request_sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  tcp_v6_md5_do_add (struct sock*,struct in6_addr*,char*,int /*<<< orphan*/ ) ; 
 struct tcp_md5sig_key* tcp_v6_md5_do_lookup (struct sock*,struct in6_addr*) ; 
 int /*<<< orphan*/  tcp_valid_rtt_meas (struct sock*,scalar_t__) ; 
 scalar_t__ xfrm_lookup (int /*<<< orphan*/ ,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock * tcp_v6_syn_recv_sock(struct sock *sk, struct sk_buff *skb,
					  struct request_sock *req,
					  struct dst_entry *dst)
{
	struct inet6_request_sock *treq;
	struct ipv6_pinfo *newnp, *np = inet6_sk(sk);
	struct tcp6_sock *newtcp6sk;
	struct inet_sock *newinet;
	struct tcp_sock *newtp;
	struct sock *newsk;
	struct ipv6_txoptions *opt;
#ifdef CONFIG_TCP_MD5SIG
	struct tcp_md5sig_key *key;
#endif

	if (skb->protocol == htons(ETH_P_IP)) {
		/*
		 *	v6 mapped
		 */

		newsk = tcp_v4_syn_recv_sock(sk, skb, req, dst);

		if (newsk == NULL)
			return NULL;

		newtcp6sk = (struct tcp6_sock *)newsk;
		inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;

		newinet = inet_sk(newsk);
		newnp = inet6_sk(newsk);
		newtp = tcp_sk(newsk);

		memcpy(newnp, np, sizeof(struct ipv6_pinfo));

		ipv6_addr_set(&newnp->daddr, 0, 0, htonl(0x0000FFFF),
			      newinet->daddr);

		ipv6_addr_set(&newnp->saddr, 0, 0, htonl(0x0000FFFF),
			      newinet->saddr);

		ipv6_addr_copy(&newnp->rcv_saddr, &newnp->saddr);

		inet_csk(newsk)->icsk_af_ops = &ipv6_mapped;
		newsk->sk_backlog_rcv = tcp_v4_do_rcv;
#ifdef CONFIG_TCP_MD5SIG
		newtp->af_specific = &tcp_sock_ipv6_mapped_specific;
#endif

		newnp->pktoptions  = NULL;
		newnp->opt	   = NULL;
		newnp->mcast_oif   = inet6_iif(skb);
		newnp->mcast_hops  = ipv6_hdr(skb)->hop_limit;
		sk_extended(newsk)->rcv_tos = ipv6_tclass(ipv6_hdr(skb));

		/*
		 * No need to charge this sock to the relevant IPv6 refcnt debug socks count
		 * here, tcp_create_openreq_child now does this for us, see the comment in
		 * that function for the gory details. -acme
		 */

		/* It is tricky place. Until this moment IPv4 tcp
		   worked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		tcp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		return newsk;
	}

	treq = inet6_rsk(req);
	opt = np->opt;

	if (sk_acceptq_is_full(sk))
		goto out_overflow;

	if (dst == NULL) {
		struct in6_addr *final_p = NULL, final;
		struct flowi fl;

		memset(&fl, 0, sizeof(fl));
		fl.proto = IPPROTO_TCP;
		ipv6_addr_copy(&fl.fl6_dst, &treq->rmt_addr);
		if (opt && opt->srcrt) {
			struct rt0_hdr *rt0 = (struct rt0_hdr *) opt->srcrt;
			ipv6_addr_copy(&final, &fl.fl6_dst);
			ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
			final_p = &final;
		}
		ipv6_addr_copy(&fl.fl6_src, &treq->loc_addr);
		fl.oif = sk->sk_bound_dev_if;
		fl.fl_ip_dport = inet_rsk(req)->rmt_port;
		fl.fl_ip_sport = inet_rsk(req)->loc_port;
		security_req_classify_flow(req, &fl);

		if (ip6_dst_lookup(sk, &dst, &fl))
			goto out;

		if (final_p)
			ipv6_addr_copy(&fl.fl6_dst, final_p);

		if ((xfrm_lookup(sock_net(sk), &dst, &fl, sk, 0)) < 0)
			goto out;
	}

	newsk = tcp_create_openreq_child(sk, req, skb);
	if (newsk == NULL)
		goto out_nonewsk;

	/*
	 * No need to charge this sock to the relevant IPv6 refcnt debug socks
	 * count here, tcp_create_openreq_child now does this for us, see the
	 * comment in that function for the gory details. -acme
	 */

	newsk->sk_gso_type = SKB_GSO_TCPV6;
	__ip6_dst_store(newsk, dst, NULL, NULL);

	newtcp6sk = (struct tcp6_sock *)newsk;
	inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;

	newtp = tcp_sk(newsk);
	newinet = inet_sk(newsk);
	newnp = inet6_sk(newsk);

	memcpy(newnp, np, sizeof(struct ipv6_pinfo));

	ipv6_addr_copy(&newnp->daddr, &treq->rmt_addr);
	ipv6_addr_copy(&newnp->saddr, &treq->loc_addr);
	ipv6_addr_copy(&newnp->rcv_saddr, &treq->loc_addr);
	newsk->sk_bound_dev_if = treq->iif;

	/* Now IPv6 options...

	   First: no IPv4 options.
	 */
	newinet->opt = NULL;
	newnp->ipv6_fl_list = NULL;

	/* Clone RX bits */
	newnp->rxopt.all = np->rxopt.all;

	/* Clone pktoptions received with SYN */
	newnp->pktoptions = NULL;
	if (treq->pktopts != NULL) {
		newnp->pktoptions = skb_clone(treq->pktopts, GFP_ATOMIC);
		kfree_skb(treq->pktopts);
		treq->pktopts = NULL;
		if (newnp->pktoptions)
			skb_set_owner_r(newnp->pktoptions, newsk);
	}
	newnp->opt	  = NULL;
	newnp->mcast_oif  = inet6_iif(skb);
	newnp->mcast_hops = ipv6_hdr(skb)->hop_limit;
	sk_extended(newsk)->rcv_tos = ipv6_tclass(ipv6_hdr(skb));

	/* Clone native IPv6 options from listening socket (if any)

	   Yes, keeping reference count would be much more clever,
	   but we make one more one thing there: reattach optmem
	   to newsk.
	 */
	if (opt) {
		newnp->opt = ipv6_dup_options(newsk, opt);
		if (opt != np->opt)
			sock_kfree_s(sk, opt, opt->tot_len);
	}

	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	if (newnp->opt)
		inet_csk(newsk)->icsk_ext_hdr_len = (newnp->opt->opt_nflen +
						     newnp->opt->opt_flen);

	tcp_mtup_init(newsk);
	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = dst_metric(dst, RTAX_ADVMSS);
	tcp_initialize_rcv_mss(newsk);
	if (tcp_rsk(req)->snt_synack)
		tcp_valid_rtt_meas(newsk,
		    tcp_time_stamp - tcp_rsk(req)->snt_synack);
	newtp->total_retrans = req->retrans;

	newinet->daddr = newinet->saddr = newinet->rcv_saddr = LOOPBACK4_IPV6;

#ifdef CONFIG_TCP_MD5SIG
	/* Copy over the MD5 key from the original socket */
	if ((key = tcp_v6_md5_do_lookup(sk, &newnp->daddr)) != NULL) {
		/* We're using one, so create a matching key
		 * on the newsk structure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		char *newkey = kmemdup(key->key, key->keylen, GFP_ATOMIC);
		if (newkey != NULL)
			tcp_v6_md5_do_add(newsk, &newnp->daddr,
					  newkey, key->keylen);
	}
#endif

	if (__inet_inherit_port(sk, newsk) < 0) {
		sock_put(newsk);
		goto out;
	}
	__inet6_hash(newsk);

	return newsk;

out_overflow:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
out_nonewsk:
	if (opt && opt != np->opt)
		sock_kfree_s(sk, opt, opt->tot_len);
	dst_release(dst);
out:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENDROPS);
	return NULL;
}