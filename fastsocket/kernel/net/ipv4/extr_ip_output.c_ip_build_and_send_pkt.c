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
struct sock {int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_protocol; } ;
struct sk_buff {int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;
struct rtable {TYPE_1__ u; int /*<<< orphan*/  rt_src; int /*<<< orphan*/  rt_dst; } ;
struct iphdr {int version; int ihl; int /*<<< orphan*/  protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  ttl; scalar_t__ frag_off; int /*<<< orphan*/  tos; } ;
struct ip_options {int optlen; } ;
struct inet_sock {int /*<<< orphan*/  tos; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IP_DF ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ip_dont_fragment (struct sock*,int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_local_out (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_build (struct sk_buff*,struct ip_options*,int /*<<< orphan*/ ,struct rtable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_select_ident (struct iphdr*,int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  ip_select_ttl (struct inet_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 

int ip_build_and_send_pkt(struct sk_buff *skb, struct sock *sk,
			  __be32 saddr, __be32 daddr, struct ip_options *opt)
{
	struct inet_sock *inet = inet_sk(sk);
	struct rtable *rt = skb_rtable(skb);
	struct iphdr *iph;

	/* Build the IP header. */
	skb_push(skb, sizeof(struct iphdr) + (opt ? opt->optlen : 0));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	iph->version  = 4;
	iph->ihl      = 5;
	iph->tos      = inet->tos;
	if (ip_dont_fragment(sk, &rt->u.dst))
		iph->frag_off = htons(IP_DF);
	else
		iph->frag_off = 0;
	iph->ttl      = ip_select_ttl(inet, &rt->u.dst);
	iph->daddr    = rt->rt_dst;
	iph->saddr    = rt->rt_src;
	iph->protocol = sk->sk_protocol;
	ip_select_ident(iph, &rt->u.dst, sk);

	if (opt && opt->optlen) {
		iph->ihl += opt->optlen>>2;
		ip_options_build(skb, opt, daddr, rt, 0);
	}

	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;

	/* Send it out. */
	return ip_local_out(skb);
}