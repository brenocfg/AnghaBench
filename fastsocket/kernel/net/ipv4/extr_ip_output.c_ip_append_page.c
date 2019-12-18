#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_protocol; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {size_t len; scalar_t__ ip_summed; int data_len; int truesize; scalar_t__ csum; scalar_t__ network_header; scalar_t__ transport_header; } ;
struct TYPE_7__ {TYPE_6__* dev; } ;
struct TYPE_8__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; int /*<<< orphan*/  rt_dst; } ;
struct page {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {int optlen; } ;
struct TYPE_10__ {int flags; int fragsize; size_t length; struct ip_options* opt; scalar_t__ dst; } ;
struct inet_sock {TYPE_4__ cork; int /*<<< orphan*/  dport; scalar_t__ hdrincl; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_12__ {int features; } ;
struct TYPE_11__ {int gso_size; int nr_frags; TYPE_3__* frags; int /*<<< orphan*/  gso_type; } ;
struct TYPE_9__ {int size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int IPCORK_OPT ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int /*<<< orphan*/  IP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LL_RESERVED_SPACE (TYPE_6__*) ; 
 int MAX_SKB_FRAGS ; 
 int MSG_PROBE ; 
 int NETIF_F_SG ; 
 int NETIF_F_UFO ; 
 int /*<<< orphan*/  SKB_GSO_UDP ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ csum_block_add (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  csum_page (struct page*,int,int) ; 
 scalar_t__ csum_sub (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_local_error (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_trim_unique (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_can_coalesce (struct sk_buff*,int,struct page*,int) ; 
 scalar_t__ skb_copy_and_csum_bits (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 struct sk_buff* skb_peek_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct sk_buff* sock_wmalloc (struct sock*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

ssize_t	ip_append_page(struct sock *sk, struct page *page,
		       int offset, size_t size, int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	struct sk_buff *skb;
	struct rtable *rt;
	struct ip_options *opt = NULL;
	int hh_len;
	int mtu;
	int len;
	int err;
	unsigned int maxfraglen, fragheaderlen, fraggap;

	if (inet->hdrincl)
		return -EPERM;

	if (flags&MSG_PROBE)
		return 0;

	if (skb_queue_empty(&sk->sk_write_queue))
		return -EINVAL;

	rt = (struct rtable *)inet->cork.dst;
	if (inet->cork.flags & IPCORK_OPT)
		opt = inet->cork.opt;

	if (!(rt->u.dst.dev->features&NETIF_F_SG))
		return -EOPNOTSUPP;

	hh_len = LL_RESERVED_SPACE(rt->u.dst.dev);
	mtu = inet->cork.fragsize;

	fragheaderlen = sizeof(struct iphdr) + (opt ? opt->optlen : 0);
	maxfraglen = ((mtu - fragheaderlen) & ~7) + fragheaderlen;

	if (inet->cork.length + size > 0xFFFF - fragheaderlen) {
		ip_local_error(sk, EMSGSIZE, rt->rt_dst, inet->dport, mtu);
		return -EMSGSIZE;
	}

	if ((skb = skb_peek_tail(&sk->sk_write_queue)) == NULL)
		return -EINVAL;

	inet->cork.length += size;
	if ((size + skb->len > mtu) &&
	    (sk->sk_protocol == IPPROTO_UDP) &&
	    (rt->u.dst.dev->features & NETIF_F_UFO)) {
		skb_shinfo(skb)->gso_size = mtu - fragheaderlen;
		skb_shinfo(skb)->gso_type = SKB_GSO_UDP;
	}


	while (size > 0) {
		int i;

		if (skb_is_gso(skb))
			len = size;
		else {

			/* Check if the remaining data fits into current packet. */
			len = mtu - skb->len;
			if (len < size)
				len = maxfraglen - skb->len;
		}
		if (len <= 0) {
			struct sk_buff *skb_prev;
			int alloclen;

			skb_prev = skb;
			fraggap = skb_prev->len - maxfraglen;

			alloclen = fragheaderlen + hh_len + fraggap + 15;
			skb = sock_wmalloc(sk, alloclen, 1, sk->sk_allocation);
			if (unlikely(!skb)) {
				err = -ENOBUFS;
				goto error;
			}

			/*
			 *	Fill in the control structures
			 */
			skb->ip_summed = CHECKSUM_NONE;
			skb->csum = 0;
			skb_reserve(skb, hh_len);

			/*
			 *	Find where to start putting bytes.
			 */
			skb_put(skb, fragheaderlen + fraggap);
			skb_reset_network_header(skb);
			skb->transport_header = (skb->network_header +
						 fragheaderlen);
			if (fraggap) {
				skb->csum = skb_copy_and_csum_bits(skb_prev,
								   maxfraglen,
						    skb_transport_header(skb),
								   fraggap, 0);
				skb_prev->csum = csum_sub(skb_prev->csum,
							  skb->csum);
				pskb_trim_unique(skb_prev, maxfraglen);
			}

			/*
			 * Put the packet on the pending queue.
			 */
			__skb_queue_tail(&sk->sk_write_queue, skb);
			continue;
		}

		i = skb_shinfo(skb)->nr_frags;
		if (len > size)
			len = size;
		if (skb_can_coalesce(skb, i, page, offset)) {
			skb_shinfo(skb)->frags[i-1].size += len;
		} else if (i < MAX_SKB_FRAGS) {
			get_page(page);
			skb_fill_page_desc(skb, i, page, offset, len);
		} else {
			err = -EMSGSIZE;
			goto error;
		}

		if (skb->ip_summed == CHECKSUM_NONE) {
			__wsum csum;
			csum = csum_page(page, offset, len);
			skb->csum = csum_block_add(skb->csum, csum, skb->len);
		}

		skb->len += len;
		skb->data_len += len;
		skb->truesize += len;
		atomic_add(len, &sk->sk_wmem_alloc);
		offset += len;
		size -= len;
	}
	return 0;

error:
	inet->cork.length -= size;
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTDISCARDS);
	return err;
}