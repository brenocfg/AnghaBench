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
struct inet_frags {int dummy; } ;
struct inet_frag_queue {int last_in; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_unlink (struct inet_frag_queue*,struct inet_frags*) ; 

void inet_frag_kill(struct inet_frag_queue *fq, struct inet_frags *f)
{
	if (del_timer(&fq->timer))
		atomic_dec(&fq->refcnt);

	if (!(fq->last_in & INET_FRAG_COMPLETE)) {
		fq_unlink(fq, f);
		atomic_dec(&fq->refcnt);
		fq->last_in |= INET_FRAG_COMPLETE;
	}
}