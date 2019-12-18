#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_err_soft; scalar_t__ sk_route_caps; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_protocol; } ;
struct sk_buff {struct sock* sk; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct in6_addr {int dummy; } ;
struct ipv6_pinfo {TYPE_1__* opt; struct in6_addr daddr; int /*<<< orphan*/  dst_cookie; int /*<<< orphan*/  flow_label; struct in6_addr saddr; } ;
struct inet_sock {int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; } ;
struct flowi {struct in6_addr fl6_dst; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  oif; int /*<<< orphan*/  fl6_flowlabel; struct in6_addr fl6_src; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_2__ {scalar_t__ srcrt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_ECN_flow_xmit (struct sock*,int /*<<< orphan*/ ) ; 
 struct dst_entry* __inet6_csk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inet6_csk_dst_store (struct sock*,struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_clone (struct dst_entry*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int ip6_xmit (struct sock*,struct sk_buff*,struct flowi*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,struct flowi*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int xfrm_lookup (int /*<<< orphan*/ ,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 

int inet6_csk_xmit(struct sk_buff *skb, int ipfragok)
{
	struct sock *sk = skb->sk;
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct flowi fl;
	struct dst_entry *dst;
	struct in6_addr *final_p = NULL, final;

	memset(&fl, 0, sizeof(fl));
	fl.proto = sk->sk_protocol;
	ipv6_addr_copy(&fl.fl6_dst, &np->daddr);
	ipv6_addr_copy(&fl.fl6_src, &np->saddr);
	fl.fl6_flowlabel = np->flow_label;
	IP6_ECN_flow_xmit(sk, fl.fl6_flowlabel);
	fl.oif = sk->sk_bound_dev_if;
	fl.fl_ip_sport = inet->sport;
	fl.fl_ip_dport = inet->dport;
	security_sk_classify_flow(sk, &fl);

	if (np->opt && np->opt->srcrt) {
		struct rt0_hdr *rt0 = (struct rt0_hdr *)np->opt->srcrt;
		ipv6_addr_copy(&final, &fl.fl6_dst);
		ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
		final_p = &final;
	}

	dst = __inet6_csk_dst_check(sk, np->dst_cookie);

	if (dst == NULL) {
		int err = ip6_dst_lookup(sk, &dst, &fl);

		if (err) {
			sk->sk_err_soft = -err;
			kfree_skb(skb);
			return err;
		}

		if (final_p)
			ipv6_addr_copy(&fl.fl6_dst, final_p);

		if ((err = xfrm_lookup(sock_net(sk), &dst, &fl, sk, 0)) < 0) {
			sk->sk_route_caps = 0;
			kfree_skb(skb);
			return err;
		}

		__inet6_csk_dst_store(sk, dst, NULL, NULL);
	}

	skb_dst_set(skb, dst_clone(dst));

	/* Restore final destination back after routing done */
	ipv6_addr_copy(&fl.fl6_dst, &np->daddr);

	return ip6_xmit(sk, skb, &fl, np->opt, 0);
}