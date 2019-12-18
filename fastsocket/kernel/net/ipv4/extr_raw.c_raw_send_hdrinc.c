#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; } ;
struct sk_buff {int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; } ;
struct TYPE_8__ {TYPE_4__* dev; } ;
struct TYPE_7__ {TYPE_2__ dst; } ;
struct rtable {TYPE_1__ u; scalar_t__ rt_src; int /*<<< orphan*/  rt_dst; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; scalar_t__ protocol; scalar_t__ check; int /*<<< orphan*/  id; int /*<<< orphan*/  tot_len; scalar_t__ saddr; } ;
struct inet_sock {int /*<<< orphan*/  recverr; int /*<<< orphan*/  dport; } ;
struct icmphdr {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {size_t mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 scalar_t__ IPPROTO_ICMP ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ LL_ALLOCATED_SPACE (TYPE_4__*) ; 
 int /*<<< orphan*/  LL_RESERVED_SPACE (TYPE_4__*) ; 
 unsigned int MSG_DONTWAIT ; 
 unsigned int MSG_PROBE ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  dst_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  dst_output ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  icmp_out_count (struct net*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ip_fast_csum (unsigned char*,int) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_local_error (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ip_select_ident (struct iphdr*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcpy_fromiovecend (void*,void*,int /*<<< orphan*/ ,size_t) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,scalar_t__,unsigned int,int*) ; 
 struct net* sock_net (struct sock*) ; 

__attribute__((used)) static int raw_send_hdrinc(struct sock *sk, void *from, size_t length,
			struct rtable *rt,
			unsigned int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	struct net *net = sock_net(sk);
	struct iphdr *iph;
	struct sk_buff *skb;
	unsigned int iphlen;
	int err;

	if (length > rt->u.dst.dev->mtu) {
		ip_local_error(sk, EMSGSIZE, rt->rt_dst, inet->dport,
			       rt->u.dst.dev->mtu);
		return -EMSGSIZE;
	}
	if (flags&MSG_PROBE)
		goto out;

	skb = sock_alloc_send_skb(sk,
				  length + LL_ALLOCATED_SPACE(rt->u.dst.dev) + 15,
				  flags & MSG_DONTWAIT, &err);
	if (skb == NULL)
		goto error;
	skb_reserve(skb, LL_RESERVED_SPACE(rt->u.dst.dev));

	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;
	skb_dst_set(skb, dst_clone(&rt->u.dst));

	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	skb_put(skb, length);

	skb->ip_summed = CHECKSUM_NONE;

	skb->transport_header = skb->network_header;
	err = -EFAULT;
	if (memcpy_fromiovecend((void *)iph, from, 0, length))
		goto error_free;

	iphlen = iph->ihl * 4;

	/*
	 * We don't want to modify the ip header, but we do need to
	 * be sure that it won't cause problems later along the network
	 * stack.  Specifically we want to make sure that iph->ihl is a
	 * sane value.  If ihl points beyond the length of the buffer passed
	 * in, reject the frame as invalid
	 */
	err = -EINVAL;
	if (iphlen > length)
		goto error_free;

	if (iphlen >= sizeof(*iph)) {
		if (!iph->saddr)
			iph->saddr = rt->rt_src;
		iph->check   = 0;
		iph->tot_len = htons(length);
		if (!iph->id)
			ip_select_ident(iph, &rt->u.dst, NULL);

		iph->check = ip_fast_csum((unsigned char *)iph, iph->ihl);
	}
	if (iph->protocol == IPPROTO_ICMP)
		icmp_out_count(net, ((struct icmphdr *)
			skb_transport_header(skb))->type);

	err = NF_HOOK(PF_INET, NF_INET_LOCAL_OUT, skb, NULL, rt->u.dst.dev,
		      dst_output);
	if (err > 0)
		err = net_xmit_errno(err);
	if (err)
		goto error;
out:
	return 0;

error_free:
	kfree_skb(skb);
error:
	IP_INC_STATS(net, IPSTATS_MIB_OUTDISCARDS);
	if (err == -ENOBUFS && !inet->recverr)
		err = 0;
	return err;
}