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
struct kqueue {int /*<<< orphan*/  kq_count; } ;
struct kqtailq {int dummy; } ;
struct knote {int kn_status; } ;

/* Variables and functions */
 int KN_ACTIVE ; 
 int KN_DISABLED ; 
 int KN_DROPPING ; 
 int KN_QUEUED ; 
 int KN_STAYACTIVE ; 
 int KN_SUPPRESSED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct kqtailq*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_tqe ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 struct kqtailq* knote_get_queue (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 

__attribute__((used)) static int
knote_enqueue(struct knote *kn)
{
	if ((kn->kn_status & (KN_ACTIVE | KN_STAYACTIVE)) == 0 ||
	    (kn->kn_status & (KN_DISABLED | KN_SUPPRESSED | KN_DROPPING)))
		return 0;

	if ((kn->kn_status & KN_QUEUED) == 0) {
		struct kqtailq *queue = knote_get_queue(kn);
		struct kqueue *kq = knote_get_kq(kn);

		kqlock_held(kq);
		TAILQ_INSERT_TAIL(queue, kn, kn_tqe);
		kn->kn_status |= KN_QUEUED;
		kq->kq_count++;
		return 1;
	}
	return ((kn->kn_status & KN_STAYACTIVE) != 0);
}