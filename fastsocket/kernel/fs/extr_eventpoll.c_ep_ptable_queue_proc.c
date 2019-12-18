#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct file {int f_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct eppoll_entry {int /*<<< orphan*/  llink; TYPE_1__ wait; struct epitem* base; int /*<<< orphan*/ * whead; } ;
struct epitem {int nwait; int /*<<< orphan*/  pwqlist; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int FMODE_SINGLE_WAKEUP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WQ_FLAG_LOADBALANCE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct epitem* ep_item_from_epqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep_poll_callback ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct eppoll_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwq_cache ; 

__attribute__((used)) static void ep_ptable_queue_proc(struct file *file, wait_queue_head_t *whead,
				 poll_table *pt)
{
	struct epitem *epi = ep_item_from_epqueue(pt);
	struct eppoll_entry *pwq;

	if (epi->nwait >= 0 && (pwq = kmem_cache_alloc(pwq_cache, GFP_KERNEL))) {
		init_waitqueue_func_entry(&pwq->wait, ep_poll_callback);
		pwq->whead = whead;
		pwq->base = epi;
		if (file->f_mode & FMODE_SINGLE_WAKEUP) {
			pwq->wait.flags |= WQ_FLAG_LOADBALANCE;
		}
		add_wait_queue(whead, &pwq->wait);
		list_add_tail(&pwq->llink, &epi->pwqlist);
		epi->nwait++;
	} else {
		/* We have to signal that an error occurred */
		epi->nwait = -1;
	}
}