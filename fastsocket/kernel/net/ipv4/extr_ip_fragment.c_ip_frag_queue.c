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
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  truesize; int /*<<< orphan*/  tstamp; struct net_device* dev; struct sk_buff* next; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_7__ {int last_in; int len; int meat; int max_size; TYPE_4__* net; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  stamp; struct sk_buff* fragments; } ;
struct ipq {TYPE_1__ q; int /*<<< orphan*/  iif; } ;
struct TYPE_12__ {int offset; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  lru_list; int /*<<< orphan*/  mem; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int frag_off; } ;

/* Variables and functions */
 void* CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 TYPE_6__* FRAG_CB (struct sk_buff*) ; 
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_FIRST_IN ; 
 int INET_FRAG_LAST_IN ; 
 TYPE_5__* IPCB (struct sk_buff*) ; 
 int IPSKB_FRAG_COMPLETE ; 
 int /*<<< orphan*/  IP_DF ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_kfree_skb (TYPE_4__*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int htons (int /*<<< orphan*/ ) ; 
 TYPE_3__ ip4_frags ; 
 int ip_frag_reasm (struct ipq*,struct sk_buff*,struct net_device*) ; 
 int ip_frag_reinit (struct ipq*) ; 
 int ip_frag_too_far (struct ipq*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ipq_kill (struct ipq*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/ * pskb_pull (struct sk_buff*,int) ; 
 int pskb_trim_rcsum (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_frag_queue(struct ipq *qp, struct sk_buff *skb)
{
	struct sk_buff *prev, *next;
	struct net_device *dev;
	int flags, offset;
	int ihl, end;
	int err = -ENOENT;

	if (qp->q.last_in & INET_FRAG_COMPLETE)
		goto err;

	if (!(IPCB(skb)->flags & IPSKB_FRAG_COMPLETE) &&
	    unlikely(ip_frag_too_far(qp)) &&
	    unlikely(err = ip_frag_reinit(qp))) {
		ipq_kill(qp);
		goto err;
	}

	offset = ntohs(ip_hdr(skb)->frag_off);
	flags = offset & ~IP_OFFSET;
	offset &= IP_OFFSET;
	offset <<= 3;		/* offset is in 8-byte chunks */
	ihl = ip_hdrlen(skb);

	/* Determine the position of this fragment. */
	end = offset + skb->len - ihl;
	err = -EINVAL;

	/* Is this the final fragment? */
	if ((flags & IP_MF) == 0) {
		/* If we already have some bits beyond end
		 * or have different end, the segment is corrrupted.
		 */
		if (end < qp->q.len ||
		    ((qp->q.last_in & INET_FRAG_LAST_IN) && end != qp->q.len))
			goto err;
		qp->q.last_in |= INET_FRAG_LAST_IN;
		qp->q.len = end;
	} else {
		if (end&7) {
			end &= ~7;
			if (skb->ip_summed != CHECKSUM_UNNECESSARY)
				skb->ip_summed = CHECKSUM_NONE;
		}
		if (end > qp->q.len) {
			/* Some bits beyond end -> corruption. */
			if (qp->q.last_in & INET_FRAG_LAST_IN)
				goto err;
			qp->q.len = end;
		}
	}
	if (end == offset)
		goto err;

	err = -ENOMEM;
	if (pskb_pull(skb, ihl) == NULL)
		goto err;

	err = pskb_trim_rcsum(skb, end - offset);
	if (err)
		goto err;

	/* Find out which fragments are in front and at the back of us
	 * in the chain of fragments so far.  We must know where to put
	 * this fragment, right?
	 */
	prev = NULL;
	for (next = qp->q.fragments; next != NULL; next = next->next) {
		if (FRAG_CB(next)->offset >= offset)
			break;	/* bingo! */
		prev = next;
	}

	/* We found where to put this one.  Check for overlap with
	 * preceding fragment, and, if needed, align things so that
	 * any overlaps are eliminated.
	 */
	if (prev) {
		int i = (FRAG_CB(prev)->offset + prev->len) - offset;

		if (i > 0) {
			offset += i;
			err = -EINVAL;
			if (end <= offset)
				goto err;
			err = -ENOMEM;
			if (!pskb_pull(skb, i))
				goto err;
			if (skb->ip_summed != CHECKSUM_UNNECESSARY)
				skb->ip_summed = CHECKSUM_NONE;
		}
	}

	err = -ENOMEM;

	while (next && FRAG_CB(next)->offset < end) {
		int i = end - FRAG_CB(next)->offset; /* overlap is 'i' bytes */

		if (i < next->len) {
			/* Eat head of the next overlapped fragment
			 * and leave the loop. The next ones cannot overlap.
			 */
			if (!pskb_pull(next, i))
				goto err;
			FRAG_CB(next)->offset += i;
			qp->q.meat -= i;
			if (next->ip_summed != CHECKSUM_UNNECESSARY)
				next->ip_summed = CHECKSUM_NONE;
			break;
		} else {
			struct sk_buff *free_it = next;

			/* Old fragment is completely overridden with
			 * new one drop it.
			 */
			next = next->next;

			if (prev)
				prev->next = next;
			else
				qp->q.fragments = next;

			qp->q.meat -= free_it->len;
			frag_kfree_skb(qp->q.net, free_it, NULL);
		}
	}

	FRAG_CB(skb)->offset = offset;

	/* Insert this fragment in the chain of fragments. */
	skb->next = next;
	if (prev)
		prev->next = skb;
	else
		qp->q.fragments = skb;

	dev = skb->dev;
	if (dev) {
		qp->iif = dev->ifindex;
		skb->dev = NULL;
	}
	qp->q.stamp = skb->tstamp;
	qp->q.meat += skb->len;
	atomic_add(skb->truesize, &qp->q.net->mem);
	if (offset == 0)
		qp->q.last_in |= INET_FRAG_FIRST_IN;

	if (ip_hdr(skb)->frag_off & htons(IP_DF) &&
	    skb->len + ihl > qp->q.max_size)
		qp->q.max_size = skb->len + ihl;

	if (qp->q.last_in == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    qp->q.meat == qp->q.len)
		return ip_frag_reasm(qp, prev, dev);

	write_lock(&ip4_frags.lock);
	list_move_tail(&qp->q.lru_list, &qp->q.net->lru_list);
	write_unlock(&ip4_frags.lock);
	return -EINPROGRESS;

err:
	kfree_skb(skb);
	return err;
}