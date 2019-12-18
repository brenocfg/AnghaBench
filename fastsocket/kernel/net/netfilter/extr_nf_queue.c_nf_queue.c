#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {struct sk_buff* next; void* protocol; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int __nf_queue (struct sk_buff*,struct list_head*,int /*<<< orphan*/ ,unsigned int,struct net_device*,struct net_device*,int (*) (struct sk_buff*),unsigned int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int nf_queue(struct sk_buff *skb,
	     struct list_head *elem,
	     u_int8_t pf, unsigned int hook,
	     struct net_device *indev,
	     struct net_device *outdev,
	     int (*okfn)(struct sk_buff *),
	     unsigned int queuenum)
{
	struct sk_buff *segs;
	int err;
	unsigned int queued;

	if (!skb_is_gso(skb))
		return __nf_queue(skb, elem, pf, hook, indev, outdev, okfn,
				  queuenum);

	switch (pf) {
	case NFPROTO_IPV4:
		skb->protocol = htons(ETH_P_IP);
		break;
	case NFPROTO_IPV6:
		skb->protocol = htons(ETH_P_IPV6);
		break;
	}

	segs = skb_gso_segment(skb, 0);
	/* Does not use PTR_ERR to limit the number of error codes that can be
	 * returned by nf_queue.  For instance, callers rely on -ECANCELED to mean
	 * 'ignore this hook'.
	 */
	if (IS_ERR(segs))
		return -EINVAL;

	queued = 0;
	err = 0;
	do {
		struct sk_buff *nskb = segs->next;

		segs->next = NULL;
		if (err == 0)
			err = __nf_queue(segs, elem, pf, hook, indev,
					   outdev, okfn, queuenum);
		if (err == 0)
			queued++;
		else
			kfree_skb(segs);
		segs = nskb;
	} while (segs);

	/* also free orig skb if only some segments were queued */
	if (unlikely(err && queued))
		err = 0;
	if (err == 0)
		kfree_skb(skb);
	return err;
}