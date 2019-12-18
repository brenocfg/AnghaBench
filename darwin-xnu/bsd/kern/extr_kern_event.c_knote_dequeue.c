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
 int KN_QUEUED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct kqtailq*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_tqe ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 struct kqtailq* knote_get_queue (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 

__attribute__((used)) static void
knote_dequeue(struct knote *kn)
{
	struct kqueue *kq = knote_get_kq(kn);
	struct kqtailq *queue;

	kqlock_held(kq);

	if ((kn->kn_status & KN_QUEUED) == 0)
		return;

	queue = knote_get_queue(kn);
	TAILQ_REMOVE(queue, kn, kn_tqe);
	kn->kn_status &= ~KN_QUEUED;
	kq->kq_count--;
}