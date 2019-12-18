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
struct sock {int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {scalar_t__ data; int local_df; scalar_t__ len; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * destructor; scalar_t__ truesize; int /*<<< orphan*/  data_len; struct sk_buff* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_idev; TYPE_3__ u; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {unsigned char nexthdr; struct in6_addr daddr; struct in6_addr saddr; int /*<<< orphan*/  hop_limit; } ;
struct ipv6_txoptions {scalar_t__ opt_nflen; scalar_t__ opt_flen; } ;
struct TYPE_7__ {int /*<<< orphan*/  hop_limit; scalar_t__ tclass; struct ipv6_txoptions* opt; } ;
struct ipv6_pinfo {scalar_t__ pmtudisc; TYPE_2__ cork; } ;
struct flowi {unsigned char proto; int fl6_flowlabel; struct in6_addr fl6_src; struct in6_addr fl6_dst; } ;
struct TYPE_6__ {struct flowi fl; scalar_t__ dst; } ;
struct inet_sock {TYPE_1__ cork; } ;
struct inet6_dev {int dummy; } ;
typedef  int __be32 ;
struct TYPE_10__ {int /*<<< orphan*/  icmp6_type; } ;
struct TYPE_9__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6MSGOUT_INC_STATS_BH (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_INC_STATS_BH (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_MIB_OUTMSGS ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 scalar_t__ IPV6_PMTUDISC_DO ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ *) ; 
 int htonl (int) ; 
 TYPE_5__* icmp6_hdr (struct sk_buff*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_cork_release (struct inet_sock*,struct ipv6_pinfo*) ; 
 struct inet6_dev* ip6_dst_idev (int /*<<< orphan*/ ) ; 
 int ip6_local_out (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_push_frag_opts (struct sk_buff*,struct ipv6_txoptions*,unsigned char*) ; 
 int /*<<< orphan*/  ipv6_push_nfrag_opts (struct sk_buff*,struct ipv6_txoptions*,unsigned char*,struct in6_addr**) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 struct net* sock_net (struct sock*) ; 

int ip6_push_pending_frames(struct sock *sk)
{
	struct sk_buff *skb, *tmp_skb;
	struct sk_buff **tail_skb;
	struct in6_addr final_dst_buf, *final_dst = &final_dst_buf;
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net *net = sock_net(sk);
	struct ipv6hdr *hdr;
	struct ipv6_txoptions *opt = np->cork.opt;
	struct rt6_info *rt = (struct rt6_info *)inet->cork.dst;
	struct flowi *fl = &inet->cork.fl;
	unsigned char proto = fl->proto;
	int err = 0;

	if ((skb = __skb_dequeue(&sk->sk_write_queue)) == NULL)
		goto out;
	tail_skb = &(skb_shinfo(skb)->frag_list);

	/* move skb->data to ip header from ext header */
	if (skb->data < skb_network_header(skb))
		__skb_pull(skb, skb_network_offset(skb));
	while ((tmp_skb = __skb_dequeue(&sk->sk_write_queue)) != NULL) {
		__skb_pull(tmp_skb, skb_network_header_len(skb));
		*tail_skb = tmp_skb;
		tail_skb = &(tmp_skb->next);
		skb->len += tmp_skb->len;
		skb->data_len += tmp_skb->len;
		skb->truesize += tmp_skb->truesize;
		tmp_skb->destructor = NULL;
		tmp_skb->sk = NULL;
	}

	/* Allow local fragmentation. */
	if (np->pmtudisc < IPV6_PMTUDISC_DO)
		skb->local_df = 1;

	ipv6_addr_copy(final_dst, &fl->fl6_dst);
	__skb_pull(skb, skb_network_header_len(skb));
	if (opt && opt->opt_flen)
		ipv6_push_frag_opts(skb, opt, &proto);
	if (opt && opt->opt_nflen)
		ipv6_push_nfrag_opts(skb, opt, &proto, &final_dst);

	skb_push(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	*(__be32*)hdr = fl->fl6_flowlabel |
		     htonl(0x60000000 | ((int)np->cork.tclass << 20));

	hdr->hop_limit = np->cork.hop_limit;
	hdr->nexthdr = proto;
	ipv6_addr_copy(&hdr->saddr, &fl->fl6_src);
	ipv6_addr_copy(&hdr->daddr, final_dst);

	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;

	skb_dst_set(skb, dst_clone(&rt->u.dst));
	IP6_UPD_PO_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	if (proto == IPPROTO_ICMPV6) {
		struct inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

		ICMP6MSGOUT_INC_STATS_BH(net, idev, icmp6_hdr(skb)->icmp6_type);
		ICMP6_INC_STATS_BH(net, idev, ICMP6_MIB_OUTMSGS);
	}

	err = ip6_local_out(skb);
	if (err) {
		if (err > 0)
			err = net_xmit_errno(err);
		if (err)
			goto error;
	}

out:
	ip6_cork_release(inet, np);
	return err;
error:
	IP6_INC_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
	goto out;
}