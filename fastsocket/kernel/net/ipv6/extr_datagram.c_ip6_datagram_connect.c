#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int* s6_addr; int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int sin6_flowinfo; scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_port; struct in6_addr sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_3__ sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_bound_dev_if; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_protocol; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct ipv6_pinfo {scalar_t__ mcast_oif; int flow_label; struct in6_addr saddr; struct in6_addr daddr; struct in6_addr rcv_saddr; TYPE_2__* opt; scalar_t__ sndflow; } ;
struct ip6_flowlabel {TYPE_1__* opt; struct in6_addr dst; } ;
struct inet_sock {int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi {int fl6_flowlabel; scalar_t__ oif; struct in6_addr fl6_src; struct in6_addr fl6_dst; int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_5__ {scalar_t__ srcrt; } ;
struct TYPE_4__ {scalar_t__ srcrt; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int EREMOTE ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_MULTICAST ; 
 int IPV6_FLOWINFO_MASK ; 
 int IPV6_FLOWLABEL_MASK ; 
 int /*<<< orphan*/  LOOPBACK4_IPV6 ; 
 int SIN6_LEN_RFC2133 ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  XFRM_LOOKUP_WAIT ; 
 scalar_t__ __ipv6_only_sock (struct sock*) ; 
 int __xfrm_lookup (int /*<<< orphan*/ ,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 
 struct ip6_flowlabel* fl6_sock_lookup (struct sock*,int) ; 
 int /*<<< orphan*/  fl6_sock_release (struct ip6_flowlabel*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip4_datagram_connect (struct sock*,struct sockaddr*,int) ; 
 int ip6_dst_blackhole (struct sock*,struct dst_entry**,struct flowi*) ; 
 int ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  ip6_dst_store (struct sock*,struct dst_entry*,struct in6_addr*,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_set (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (struct in6_addr*) ; 
 scalar_t__ ipv6_mapped_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,struct flowi*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

int ip6_datagram_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct sockaddr_in6	*usin = (struct sockaddr_in6 *) uaddr;
	struct inet_sock      	*inet = inet_sk(sk);
	struct ipv6_pinfo      	*np = inet6_sk(sk);
	struct in6_addr		*daddr, *final_p = NULL, final;
	struct dst_entry	*dst;
	struct flowi		fl;
	struct ip6_flowlabel	*flowlabel = NULL;
	int			addr_type;
	int			err;

	if (usin->sin6_family == AF_INET) {
		if (__ipv6_only_sock(sk))
			return -EAFNOSUPPORT;
		err = ip4_datagram_connect(sk, uaddr, addr_len);
		goto ipv4_connected;
	}

	if (addr_len < SIN6_LEN_RFC2133)
		return -EINVAL;

	if (usin->sin6_family != AF_INET6)
		return -EAFNOSUPPORT;

	memset(&fl, 0, sizeof(fl));
	if (np->sndflow) {
		fl.fl6_flowlabel = usin->sin6_flowinfo&IPV6_FLOWINFO_MASK;
		if (fl.fl6_flowlabel&IPV6_FLOWLABEL_MASK) {
			flowlabel = fl6_sock_lookup(sk, fl.fl6_flowlabel);
			if (flowlabel == NULL)
				return -EINVAL;
			ipv6_addr_copy(&usin->sin6_addr, &flowlabel->dst);
		}
	}

	addr_type = ipv6_addr_type(&usin->sin6_addr);

	if (addr_type == IPV6_ADDR_ANY) {
		/*
		 *	connect to self
		 */
		usin->sin6_addr.s6_addr[15] = 0x01;
	}

	daddr = &usin->sin6_addr;

	if (addr_type == IPV6_ADDR_MAPPED) {
		struct sockaddr_in sin;

		if (__ipv6_only_sock(sk)) {
			err = -ENETUNREACH;
			goto out;
		}
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = daddr->s6_addr32[3];
		sin.sin_port = usin->sin6_port;

		err = ip4_datagram_connect(sk,
					   (struct sockaddr*) &sin,
					   sizeof(sin));

ipv4_connected:
		if (err)
			goto out;

		ipv6_addr_set(&np->daddr, 0, 0, htonl(0x0000ffff), inet->daddr);

		if (ipv6_addr_any(&np->saddr) ||
		    ipv6_mapped_addr_any(&np->saddr)) {
			ipv6_addr_set(&np->saddr, 0, 0, htonl(0x0000ffff),
				      inet->saddr);
		}

		if (ipv6_addr_any(&np->rcv_saddr) ||
		    ipv6_mapped_addr_any(&np->rcv_saddr)) {
			ipv6_addr_set(&np->rcv_saddr, 0, 0, htonl(0x0000ffff),
				      inet->rcv_saddr);
		}
		goto out;
	}

	if (addr_type&IPV6_ADDR_LINKLOCAL) {
		if (addr_len >= sizeof(struct sockaddr_in6) &&
		    usin->sin6_scope_id) {
			if (sk->sk_bound_dev_if &&
			    sk->sk_bound_dev_if != usin->sin6_scope_id) {
				err = -EINVAL;
				goto out;
			}
			sk->sk_bound_dev_if = usin->sin6_scope_id;
		}

		if (!sk->sk_bound_dev_if && (addr_type & IPV6_ADDR_MULTICAST))
			sk->sk_bound_dev_if = np->mcast_oif;

		/* Connect to link-local address requires an interface */
		if (!sk->sk_bound_dev_if) {
			err = -EINVAL;
			goto out;
		}
	}

	ipv6_addr_copy(&np->daddr, daddr);
	np->flow_label = fl.fl6_flowlabel;

	inet->dport = usin->sin6_port;

	/*
	 *	Check for a route to destination an obtain the
	 *	destination cache for it.
	 */

	fl.proto = sk->sk_protocol;
	ipv6_addr_copy(&fl.fl6_dst, &np->daddr);
	ipv6_addr_copy(&fl.fl6_src, &np->saddr);
	fl.oif = sk->sk_bound_dev_if;
	fl.fl_ip_dport = inet->dport;
	fl.fl_ip_sport = inet->sport;

	if (!fl.oif && (addr_type&IPV6_ADDR_MULTICAST))
		fl.oif = np->mcast_oif;

	security_sk_classify_flow(sk, &fl);

	if (flowlabel) {
		if (flowlabel->opt && flowlabel->opt->srcrt) {
			struct rt0_hdr *rt0 = (struct rt0_hdr *) flowlabel->opt->srcrt;
			ipv6_addr_copy(&final, &fl.fl6_dst);
			ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
			final_p = &final;
		}
	} else if (np->opt && np->opt->srcrt) {
		struct rt0_hdr *rt0 = (struct rt0_hdr *)np->opt->srcrt;
		ipv6_addr_copy(&final, &fl.fl6_dst);
		ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
		final_p = &final;
	}

	err = ip6_dst_lookup(sk, &dst, &fl);
	if (err)
		goto out;
	if (final_p)
		ipv6_addr_copy(&fl.fl6_dst, final_p);

	err = __xfrm_lookup(sock_net(sk), &dst, &fl, sk, XFRM_LOOKUP_WAIT);
	if (err < 0) {
		if (err == -EREMOTE)
			err = ip6_dst_blackhole(sk, &dst, &fl);
		if (err < 0)
			goto out;
	}

	/* source address lookup done in ip6_dst_lookup */

	if (ipv6_addr_any(&np->saddr))
		ipv6_addr_copy(&np->saddr, &fl.fl6_src);

	if (ipv6_addr_any(&np->rcv_saddr)) {
		ipv6_addr_copy(&np->rcv_saddr, &fl.fl6_src);
		inet->rcv_saddr = LOOPBACK4_IPV6;
	}

	ip6_dst_store(sk, dst,
		      ipv6_addr_equal(&fl.fl6_dst, &np->daddr) ?
		      &np->daddr : NULL,
#ifdef CONFIG_IPV6_SUBTREES
		      ipv6_addr_equal(&fl.fl6_src, &np->saddr) ?
		      &np->saddr :
#endif
		      NULL);

	sk->sk_state = TCP_ESTABLISHED;
out:
	fl6_sock_release(flowlabel);
	return err;
}