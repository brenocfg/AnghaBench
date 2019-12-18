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
struct proc {int dummy; } ;
struct kqueue {struct proc* kq_p; } ;
struct knote_lock_ctx {int dummy; } ;
struct knote {int kn_status; int /*<<< orphan*/  kn_fp; int /*<<< orphan*/  kn_id; } ;
struct TYPE_2__ {scalar_t__ f_isfd; int /*<<< orphan*/  (* f_detach ) (struct knote*) ;} ;

/* Variables and functions */
 int KN_ATTACHED ; 
 int KN_DROPPING ; 
 int KN_LOCKED ; 
 int KN_VANISHED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knote_dequeue (struct knote*) ; 
 TYPE_1__* knote_fops (struct knote*) ; 
 int /*<<< orphan*/  knote_free (struct knote*) ; 
 int /*<<< orphan*/  knote_unsuppress (struct knote*) ; 
 int /*<<< orphan*/  knote_wait_for_filter_events (struct kqueue*,struct knote*) ; 
 int /*<<< orphan*/  kq_remove_knote (struct kqueue*,struct knote*,struct proc*,struct knote_lock_ctx*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 int /*<<< orphan*/  stub1 (struct knote*) ; 

__attribute__((used)) static void
knote_drop(struct kqueue *kq, struct knote *kn, struct knote_lock_ctx *knlc)
{
	struct proc *p = kq->kq_p;

	kqlock_held(kq);

	assert((kn->kn_status & KN_DROPPING) == 0);
	if (knlc == NULL) {
		assert((kn->kn_status & KN_LOCKED) == 0);
	}
	kn->kn_status |= KN_DROPPING;

	knote_unsuppress(kn);
	knote_dequeue(kn);
	knote_wait_for_filter_events(kq, kn);

	/* If we are attached, disconnect from the source first */
	if (kn->kn_status & KN_ATTACHED) {
		knote_fops(kn)->f_detach(kn);
	}

	/* kq may be freed when kq_remove_knote() returns */
	kq_remove_knote(kq, kn, p, knlc);
	if (knote_fops(kn)->f_isfd && ((kn->kn_status & KN_VANISHED) == 0))
		fp_drop(p, kn->kn_id, kn->kn_fp, 0);

	knote_free(kn);
}