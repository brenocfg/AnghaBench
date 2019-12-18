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
struct sk_buff {struct sk_buff* next; } ;
struct netns_frags {int /*<<< orphan*/  mem; } ;
struct inet_frags {int /*<<< orphan*/  (* destructor ) (struct inet_frag_queue*) ;scalar_t__ qsize; } ;
struct inet_frag_queue {int last_in; struct netns_frags* net; struct sk_buff* fragments; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_kfree_skb (struct netns_frags*,struct inet_frags*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  kfree (struct inet_frag_queue*) ; 
 int /*<<< orphan*/  stub1 (struct inet_frag_queue*) ; 

void inet_frag_destroy(struct inet_frag_queue *q, struct inet_frags *f,
					int *work)
{
	struct sk_buff *fp;
	struct netns_frags *nf;

	WARN_ON(!(q->last_in & INET_FRAG_COMPLETE));
	WARN_ON(del_timer(&q->timer) != 0);

	/* Release all fragment data. */
	fp = q->fragments;
	nf = q->net;
	while (fp) {
		struct sk_buff *xp = fp->next;

		frag_kfree_skb(nf, f, fp, work);
		fp = xp;
	}

	if (work)
		*work -= f->qsize;
	atomic_sub(f->qsize, &nf->mem);

	if (f->destructor)
		f->destructor(q);
	kfree(q);

}