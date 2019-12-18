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
struct sock {scalar_t__ sk_protocol; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; scalar_t__ len; int local_df; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * destructor; scalar_t__ truesize; int /*<<< orphan*/  data_len; struct sk_buff* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;
struct rtable {scalar_t__ rt_type; TYPE_1__ u; int /*<<< orphan*/  rt_dst; int /*<<< orphan*/  rt_src; } ;
struct net {int dummy; } ;
struct iphdr {int version; int ihl; scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  ttl; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  tos; } ;
struct ip_options {int optlen; } ;
struct inet_sock {scalar_t__ pmtudisc; int /*<<< orphan*/  tos; int /*<<< orphan*/  mc_ttl; } ;
struct inet_cork {int flags; int /*<<< orphan*/ * dst; int /*<<< orphan*/  addr; struct ip_options* opt; } ;
struct icmphdr {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int IPCORK_OPT ; 
 scalar_t__ IPPROTO_ICMP ; 
 int /*<<< orphan*/  IP_DF ; 
 scalar_t__ IP_PMTUDISC_DO ; 
 scalar_t__ RTN_MULTICAST ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_out_count (struct net*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_cork_release (struct inet_cork*) ; 
 scalar_t__ ip_dont_fragment (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_options_build (struct sk_buff*,struct ip_options*,int /*<<< orphan*/ ,struct rtable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_select_ident (struct iphdr*,int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  ip_select_ttl (struct inet_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 struct net* sock_net (struct sock*) ; 

struct sk_buff *__ip_make_skb(struct sock *sk,
			      struct sk_buff_head *queue,
			      struct inet_cork *cork)
{
	struct sk_buff *skb, *tmp_skb;
	struct sk_buff **tail_skb;
	struct inet_sock *inet = inet_sk(sk);
	struct net *net = sock_net(sk);
	struct ip_options *opt = NULL;
	struct rtable *rt = (struct rtable *)cork->dst;
	struct iphdr *iph;
	__be16 df = 0;
	__u8 ttl;

	if ((skb = __skb_dequeue(queue)) == NULL)
		goto out;
	tail_skb = &(skb_shinfo(skb)->frag_list);

	/* move skb->data to ip header from ext header */
	if (skb->data < skb_network_header(skb))
		__skb_pull(skb, skb_network_offset(skb));
	while ((tmp_skb = __skb_dequeue(queue)) != NULL) {
		__skb_pull(tmp_skb, skb_network_header_len(skb));
		*tail_skb = tmp_skb;
		tail_skb = &(tmp_skb->next);
		skb->len += tmp_skb->len;
		skb->data_len += tmp_skb->len;
		skb->truesize += tmp_skb->truesize;
		tmp_skb->destructor = NULL;
		tmp_skb->sk = NULL;
	}

	/* Unless user demanded real pmtu discovery (IP_PMTUDISC_DO), we allow
	 * to fragment the frame generated here. No matter, what transforms
	 * how transforms change size of the packet, it will come out.
	 */
	if (inet->pmtudisc < IP_PMTUDISC_DO)
		skb->local_df = 1;

	/* DF bit is set when we want to see DF on outgoing frames.
	 * If local_df is set too, we still allow to fragment this frame
	 * locally. */
	if (inet->pmtudisc >= IP_PMTUDISC_DO ||
	    (skb->len <= dst_mtu(&rt->u.dst) &&
	     ip_dont_fragment(sk, &rt->u.dst)))
		df = htons(IP_DF);

	if (cork->flags & IPCORK_OPT)
		opt = cork->opt;

	if (rt->rt_type == RTN_MULTICAST)
		ttl = inet->mc_ttl;
	else
		ttl = ip_select_ttl(inet, &rt->u.dst);

	iph = (struct iphdr *)skb->data;
	iph->version = 4;
	iph->ihl = 5;
	if (opt) {
		iph->ihl += opt->optlen>>2;
		ip_options_build(skb, opt, cork->addr, rt, 0);
	}
	iph->tos = inet->tos;
	iph->frag_off = df;
	ip_select_ident(iph, &rt->u.dst, sk);
	iph->ttl = ttl;
	iph->protocol = sk->sk_protocol;
	iph->saddr = rt->rt_src;
	iph->daddr = rt->rt_dst;

	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;
	/*
	 * Steal rt from cork.dst to avoid a pair of atomic_inc/atomic_dec
	 * on dst refcount
	 */
	cork->dst = NULL;
	skb_dst_set(skb, &rt->u.dst);

	if (iph->protocol == IPPROTO_ICMP)
		icmp_out_count(net, ((struct icmphdr *)
			skb_transport_header(skb))->type);

	/* Netfilter gets whole the not fragmented skb. */
	ip_cork_release(cork);
out:
	return skb;
}