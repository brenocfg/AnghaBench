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
struct sk_buff {int dummy; } ;
struct nf_queue_entry {size_t pf; size_t hook; int /*<<< orphan*/  (* okfn ) (struct sk_buff*) ;int /*<<< orphan*/  outdev; int /*<<< orphan*/  indev; TYPE_1__* elem; struct sk_buff* skb; } ;
struct nf_afinfo {scalar_t__ (* reroute ) (struct sk_buff*,struct nf_queue_entry*) ;} ;
struct list_head {struct list_head* prev; } ;
struct TYPE_2__ {struct list_head list; } ;

/* Variables and functions */
 int ECANCELED ; 
 int ESRCH ; 
 int /*<<< orphan*/  INT_MIN ; 
#define  NF_ACCEPT 131 
 unsigned int NF_DROP ; 
#define  NF_QUEUE 130 
 unsigned int NF_REPEAT ; 
#define  NF_STOLEN 129 
#define  NF_STOP 128 
 unsigned int NF_VERDICT_FLAG_QUEUE_BYPASS ; 
 unsigned int NF_VERDICT_MASK ; 
 unsigned int NF_VERDICT_QBITS ; 
 int __nf_queue (struct sk_buff*,struct list_head*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct sk_buff*),unsigned int) ; 
 int /*<<< orphan*/  kfree (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct nf_afinfo* nf_get_afinfo (size_t) ; 
 int /*<<< orphan*/ ** nf_hooks ; 
 unsigned int nf_iterate (int /*<<< orphan*/ *,struct sk_buff*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head**,int /*<<< orphan*/  (*) (struct sk_buff*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_queue_entry_release_refs (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct sk_buff*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*) ; 

void nf_reinject(struct nf_queue_entry *entry, unsigned int verdict)
{
	struct sk_buff *skb = entry->skb;
	struct list_head *elem = &entry->elem->list;
	const struct nf_afinfo *afinfo;
	int err;

	rcu_read_lock();

	nf_queue_entry_release_refs(entry);

	/* Continue traversal iff userspace said ok... */
	if (verdict == NF_REPEAT) {
		elem = elem->prev;
		verdict = NF_ACCEPT;
	}

	if (verdict == NF_ACCEPT) {
		afinfo = nf_get_afinfo(entry->pf);
		if (!afinfo || afinfo->reroute(skb, entry) < 0)
			verdict = NF_DROP;
	}

	if (verdict == NF_ACCEPT) {
	next_hook:
		verdict = nf_iterate(&nf_hooks[entry->pf][entry->hook],
				     skb, entry->hook,
				     entry->indev, entry->outdev, &elem,
				     entry->okfn, INT_MIN);
	}

	switch (verdict & NF_VERDICT_MASK) {
	case NF_ACCEPT:
	case NF_STOP:
		local_bh_disable();
		entry->okfn(skb);
		local_bh_enable();
	case NF_STOLEN:
		break;
	case NF_QUEUE:
		err = __nf_queue(skb, elem, entry->pf, entry->hook,
				 entry->indev, entry->outdev, entry->okfn,
				 verdict >> NF_VERDICT_QBITS);
		if (err < 0) {
			if (err == -ECANCELED)
				goto next_hook;
			if (err == -ESRCH &&
			   (verdict & NF_VERDICT_FLAG_QUEUE_BYPASS))
				goto next_hook;
			kfree_skb(skb);
		}
		break;
	default:
		kfree_skb(skb);
	}
	rcu_read_unlock();
	kfree(entry);
	return;
}