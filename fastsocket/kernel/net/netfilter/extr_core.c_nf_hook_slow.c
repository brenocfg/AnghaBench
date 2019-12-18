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
typedef  size_t u_int8_t ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ECANCELED ; 
 int EPERM ; 
 int ESRCH ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int NF_DROP_GETERR (unsigned int) ; 
 unsigned int NF_QUEUE ; 
 unsigned int NF_STOP ; 
 unsigned int NF_VERDICT_FLAG_QUEUE_BYPASS ; 
 unsigned int NF_VERDICT_MASK ; 
 unsigned int NF_VERDICT_QBITS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct list_head** nf_hooks ; 
 unsigned int nf_iterate (struct list_head*,struct sk_buff*,unsigned int,struct net_device*,struct net_device*,struct list_head**,int (*) (struct sk_buff*),int) ; 
 int nf_queue (struct sk_buff*,struct list_head*,size_t,unsigned int,struct net_device*,struct net_device*,int (*) (struct sk_buff*),unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int nf_hook_slow(u_int8_t pf, unsigned int hook, struct sk_buff *skb,
		 struct net_device *indev,
		 struct net_device *outdev,
		 int (*okfn)(struct sk_buff *),
		 int hook_thresh)
{
	struct list_head *elem;
	unsigned int verdict;
	int ret = 0;

	/* We may already have this, but read-locks nest anyway */
	rcu_read_lock();

	elem = &nf_hooks[pf][hook];
next_hook:
	verdict = nf_iterate(&nf_hooks[pf][hook], skb, hook, indev,
			     outdev, &elem, okfn, hook_thresh);
	if (verdict == NF_ACCEPT || verdict == NF_STOP) {
		ret = 1;
	} else if ((verdict & NF_VERDICT_MASK) == NF_DROP) {
		kfree_skb(skb);
		ret = NF_DROP_GETERR(verdict);
		if (ret == 0)
			ret = -EPERM;
	} else if ((verdict & NF_VERDICT_MASK) == NF_QUEUE) {
		ret = nf_queue(skb, elem, pf, hook, indev, outdev, okfn,
			       verdict >> NF_VERDICT_QBITS);
		if (ret < 0) {
			if (ret == -ECANCELED)
				goto next_hook;
			if (ret == -ESRCH &&
			   (verdict & NF_VERDICT_FLAG_QUEUE_BYPASS))
				goto next_hook;
			kfree_skb(skb);
		}
		ret = 0;
	}
	rcu_read_unlock();
	return ret;
}