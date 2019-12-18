#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_priority; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; } ;
struct TYPE_7__ {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__ dst; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_idev; TYPE_1__ u; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  recverr; } ;
struct flowi {int dummy; } ;
struct TYPE_8__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EFAULT ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IP6_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 scalar_t__ LL_ALLOCATED_SPACE (TYPE_3__*) ; 
 int /*<<< orphan*/  LL_RESERVED_SPACE (TYPE_3__*) ; 
 unsigned int MSG_DONTWAIT ; 
 unsigned int MSG_PROBE ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  dst_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  dst_output ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_local_error (struct sock*,int,struct flowi*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int memcpy_fromiovecend (void*,void*,int /*<<< orphan*/ ,int) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,scalar_t__,unsigned int,int*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int rawv6_send_hdrinc(struct sock *sk, void *from, int length,
			struct flowi *fl, struct rt6_info *rt,
			unsigned int flags)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6hdr *iph;
	struct sk_buff *skb;
	int err;

	if (length > rt->u.dst.dev->mtu) {
		ipv6_local_error(sk, EMSGSIZE, fl, rt->u.dst.dev->mtu);
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

	skb_put(skb, length);
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);

	skb->ip_summed = CHECKSUM_NONE;

	skb->transport_header = skb->network_header;
	err = memcpy_fromiovecend((void *)iph, from, 0, length);
	if (err)
		goto error_fault;

	IP6_UPD_PO_STATS(sock_net(sk), rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	err = NF_HOOK(PF_INET6, NF_INET_LOCAL_OUT, skb, NULL, rt->u.dst.dev,
		      dst_output);
	if (err > 0)
		err = net_xmit_errno(err);
	if (err)
		goto error;
out:
	return 0;

error_fault:
	err = -EFAULT;
	kfree_skb(skb);
error:
	IP6_INC_STATS(sock_net(sk), rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
	if (err == -ENOBUFS && !np->recverr)
		err = 0;
	return err;
}