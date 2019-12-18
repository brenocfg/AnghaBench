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
typedef  scalar_t__ u32 ;
struct in6_addr {int* s6_addr; int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int sin6_flowinfo; scalar_t__ sin6_scope_id; scalar_t__ sin6_port; struct in6_addr sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; scalar_t__ sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_bound_dev_if; scalar_t__ sk_route_caps; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct ipv6_pinfo {int flow_label; struct in6_addr daddr; struct in6_addr saddr; TYPE_1__* opt; struct in6_addr rcv_saddr; scalar_t__ sndflow; } ;
struct ip6_flowlabel {struct in6_addr dst; } ;
struct inet_sock {scalar_t__ dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  saddr; } ;
struct inet_connection_sock {scalar_t__ icsk_ext_hdr_len; int /*<<< orphan*/ * icsk_af_ops; } ;
struct flowi {int fl6_flowlabel; scalar_t__ oif; struct in6_addr fl6_src; struct in6_addr fl6_dst; int /*<<< orphan*/  fl_ip_sport; scalar_t__ fl_ip_dport; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_role; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_3__ {scalar_t__ opt_nflen; scalar_t__ opt_flen; int /*<<< orphan*/ * srcrt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DCCP_CLOSED ; 
 int /*<<< orphan*/  DCCP_REQUESTING ; 
 int /*<<< orphan*/  DCCP_ROLE_CLIENT ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int EREMOTE ; 
 int /*<<< orphan*/  IP6_ECN_flow_init (int) ; 
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_MULTICAST ; 
 int IPV6_FLOWINFO_MASK ; 
 int IPV6_FLOWLABEL_MASK ; 
 int /*<<< orphan*/  LOOPBACK4_IPV6 ; 
 int SIN6_LEN_RFC2133 ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*) ; 
 int /*<<< orphan*/  XFRM_LOOKUP_WAIT ; 
 int /*<<< orphan*/  __ip6_dst_store (struct sock*,struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ __ipv6_only_sock (struct sock*) ; 
 int /*<<< orphan*/  __sk_dst_reset (struct sock*) ; 
 int __xfrm_lookup (int /*<<< orphan*/ ,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 
 int dccp_connect (struct sock*) ; 
 int /*<<< orphan*/  dccp_death_row ; 
 int /*<<< orphan*/  dccp_ipv6_af_ops ; 
 int /*<<< orphan*/  dccp_ipv6_mapped ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int dccp_v4_connect (struct sock*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  dccp_v4_do_rcv ; 
 int /*<<< orphan*/  dccp_v6_do_rcv ; 
 struct ip6_flowlabel* fl6_sock_lookup (struct sock*,int) ; 
 int /*<<< orphan*/  fl6_sock_release (struct ip6_flowlabel*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int inet6_hash_connect (int /*<<< orphan*/ *,struct sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip6_dst_blackhole (struct sock*,struct dst_entry**,struct flowi*) ; 
 int ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 scalar_t__ ipv6_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_set (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (struct in6_addr*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secure_dccpv6_sequence_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,struct flowi*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int dccp_v6_connect(struct sock *sk, struct sockaddr *uaddr,
			   int addr_len)
{
	struct sockaddr_in6 *usin = (struct sockaddr_in6 *)uaddr;
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct dccp_sock *dp = dccp_sk(sk);
	struct in6_addr *saddr = NULL, *final_p = NULL, final;
	struct flowi fl;
	struct dst_entry *dst;
	int addr_type;
	int err;

	dp->dccps_role = DCCP_ROLE_CLIENT;

	if (addr_len < SIN6_LEN_RFC2133)
		return -EINVAL;

	if (usin->sin6_family != AF_INET6)
		return -EAFNOSUPPORT;

	memset(&fl, 0, sizeof(fl));

	if (np->sndflow) {
		fl.fl6_flowlabel = usin->sin6_flowinfo & IPV6_FLOWINFO_MASK;
		IP6_ECN_flow_init(fl.fl6_flowlabel);
		if (fl.fl6_flowlabel & IPV6_FLOWLABEL_MASK) {
			struct ip6_flowlabel *flowlabel;
			flowlabel = fl6_sock_lookup(sk, fl.fl6_flowlabel);
			if (flowlabel == NULL)
				return -EINVAL;
			ipv6_addr_copy(&usin->sin6_addr, &flowlabel->dst);
			fl6_sock_release(flowlabel);
		}
	}
	/*
	 * connect() to INADDR_ANY means loopback (BSD'ism).
	 */
	if (ipv6_addr_any(&usin->sin6_addr))
		usin->sin6_addr.s6_addr[15] = 1;

	addr_type = ipv6_addr_type(&usin->sin6_addr);

	if (addr_type & IPV6_ADDR_MULTICAST)
		return -ENETUNREACH;

	if (addr_type & IPV6_ADDR_LINKLOCAL) {
		if (addr_len >= sizeof(struct sockaddr_in6) &&
		    usin->sin6_scope_id) {
			/* If interface is set while binding, indices
			 * must coincide.
			 */
			if (sk->sk_bound_dev_if &&
			    sk->sk_bound_dev_if != usin->sin6_scope_id)
				return -EINVAL;

			sk->sk_bound_dev_if = usin->sin6_scope_id;
		}

		/* Connect to link-local address requires an interface */
		if (!sk->sk_bound_dev_if)
			return -EINVAL;
	}

	ipv6_addr_copy(&np->daddr, &usin->sin6_addr);
	np->flow_label = fl.fl6_flowlabel;

	/*
	 * DCCP over IPv4
	 */
	if (addr_type == IPV6_ADDR_MAPPED) {
		u32 exthdrlen = icsk->icsk_ext_hdr_len;
		struct sockaddr_in sin;

		SOCK_DEBUG(sk, "connect: ipv4 mapped\n");

		if (__ipv6_only_sock(sk))
			return -ENETUNREACH;

		sin.sin_family = AF_INET;
		sin.sin_port = usin->sin6_port;
		sin.sin_addr.s_addr = usin->sin6_addr.s6_addr32[3];

		icsk->icsk_af_ops = &dccp_ipv6_mapped;
		sk->sk_backlog_rcv = dccp_v4_do_rcv;

		err = dccp_v4_connect(sk, (struct sockaddr *)&sin, sizeof(sin));
		if (err) {
			icsk->icsk_ext_hdr_len = exthdrlen;
			icsk->icsk_af_ops = &dccp_ipv6_af_ops;
			sk->sk_backlog_rcv = dccp_v6_do_rcv;
			goto failure;
		} else {
			ipv6_addr_set(&np->saddr, 0, 0, htonl(0x0000FFFF),
				      inet->saddr);
			ipv6_addr_set(&np->rcv_saddr, 0, 0, htonl(0x0000FFFF),
				      inet->rcv_saddr);
		}

		return err;
	}

	if (!ipv6_addr_any(&np->rcv_saddr))
		saddr = &np->rcv_saddr;

	fl.proto = IPPROTO_DCCP;
	ipv6_addr_copy(&fl.fl6_dst, &np->daddr);
	ipv6_addr_copy(&fl.fl6_src, saddr ? saddr : &np->saddr);
	fl.oif = sk->sk_bound_dev_if;
	fl.fl_ip_dport = usin->sin6_port;
	fl.fl_ip_sport = inet->sport;
	security_sk_classify_flow(sk, &fl);

	if (np->opt != NULL && np->opt->srcrt != NULL) {
		const struct rt0_hdr *rt0 = (struct rt0_hdr *)np->opt->srcrt;

		ipv6_addr_copy(&final, &fl.fl6_dst);
		ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
		final_p = &final;
	}

	err = ip6_dst_lookup(sk, &dst, &fl);
	if (err)
		goto failure;

	if (final_p)
		ipv6_addr_copy(&fl.fl6_dst, final_p);

	err = __xfrm_lookup(sock_net(sk), &dst, &fl, sk, XFRM_LOOKUP_WAIT);
	if (err < 0) {
		if (err == -EREMOTE)
			err = ip6_dst_blackhole(sk, &dst, &fl);
		if (err < 0)
			goto failure;
	}

	if (saddr == NULL) {
		saddr = &fl.fl6_src;
		ipv6_addr_copy(&np->rcv_saddr, saddr);
	}

	/* set the source address */
	ipv6_addr_copy(&np->saddr, saddr);
	inet->rcv_saddr = LOOPBACK4_IPV6;

	__ip6_dst_store(sk, dst, NULL, NULL);

	icsk->icsk_ext_hdr_len = 0;
	if (np->opt != NULL)
		icsk->icsk_ext_hdr_len = (np->opt->opt_flen +
					  np->opt->opt_nflen);

	inet->dport = usin->sin6_port;

	dccp_set_state(sk, DCCP_REQUESTING);
	err = inet6_hash_connect(&dccp_death_row, sk);
	if (err)
		goto late_failure;

	dp->dccps_iss = secure_dccpv6_sequence_number(np->saddr.s6_addr32,
						      np->daddr.s6_addr32,
						      inet->sport, inet->dport);
	err = dccp_connect(sk);
	if (err)
		goto late_failure;

	return 0;

late_failure:
	dccp_set_state(sk, DCCP_CLOSED);
	__sk_dst_reset(sk);
failure:
	inet->dport = 0;
	sk->sk_route_caps = 0;
	return err;
}