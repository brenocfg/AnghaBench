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
struct inet_frags {int /*<<< orphan*/  lock; } ;
struct inet_frag_queue {TYPE_1__* net; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  nqueues; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fq_unlink(struct inet_frag_queue *fq, struct inet_frags *f)
{
	write_lock(&f->lock);
	hlist_del(&fq->list);
	list_del(&fq->lru_list);
	fq->net->nqueues--;
	write_unlock(&f->lock);
}