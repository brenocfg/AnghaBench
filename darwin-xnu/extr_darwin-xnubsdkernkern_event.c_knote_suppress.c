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
struct kqueue {int dummy; } ;
struct kqtailq {int dummy; } ;
struct knote {int kn_status; } ;

/* Variables and functions */
 int KN_SUPPRESSED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct kqtailq*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_tqe ; 
 int /*<<< orphan*/  knote_dequeue (struct knote*) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 struct kqtailq* kqueue_get_suppressed_queue (struct kqueue*,struct knote*) ; 

__attribute__((used)) static void
knote_suppress(struct knote *kn)
{
	struct kqtailq *suppressq;
	struct kqueue *kq = knote_get_kq(kn);

	kqlock_held(kq);

	if (kn->kn_status & KN_SUPPRESSED)
		return;

	knote_dequeue(kn);
	kn->kn_status |= KN_SUPPRESSED;
	suppressq = kqueue_get_suppressed_queue(kq, kn);
	TAILQ_INSERT_TAIL(suppressq, kn, kn_tqe);
}