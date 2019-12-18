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
struct netns_frags {int /*<<< orphan*/  mem; } ;
struct inet_frags {int /*<<< orphan*/  frag_expire; int /*<<< orphan*/  qsize; int /*<<< orphan*/  (* constructor ) (struct inet_frag_queue*,void*) ;} ;
struct inet_frag_queue {struct netns_frags* net; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct inet_frag_queue* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inet_frag_queue*,void*) ; 

__attribute__((used)) static struct inet_frag_queue *inet_frag_alloc(struct netns_frags *nf,
		struct inet_frags *f, void *arg)
{
	struct inet_frag_queue *q;

	q = kzalloc(f->qsize, GFP_ATOMIC);
	if (q == NULL)
		return NULL;

	f->constructor(q, arg);
	atomic_add(f->qsize, &nf->mem);
	setup_timer(&q->timer, f->frag_expire, (unsigned long)q);
	spin_lock_init(&q->lock);
	atomic_set(&q->refcnt, 1);
	q->net = nf;

	return q;
}