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
struct waitq {int dummy; } ;
struct kqueue {int kq_state; int /*<<< orphan*/  kq_wqs; } ;
struct kqtailq {int dummy; } ;
struct knote {int kn_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_KEVENT_KQ_PROCESS_END ; 
 int /*<<< orphan*/  CAST_EVENT64_T (struct kqtailq*) ; 
 int /*<<< orphan*/  KDBG_FILTERED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEV_EVTID (int /*<<< orphan*/ ) ; 
 int KN_SUPPRESSED ; 
 int KQ_PROCESSING ; 
 int KQ_PROCWAIT ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 struct knote* TAILQ_FIRST (struct kqtailq*) ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct kqueue*) ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  knote_unsuppress (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 struct kqtailq* kqueue_get_suppressed_queue (struct kqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_wakeup64_all (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kqfile_end_processing(struct kqueue *kq)
{
	struct knote *kn;
	struct kqtailq *suppressq;
	int procwait;

	kqlock_held(kq);

	assert((kq->kq_state & (KQ_WORKQ|KQ_WORKLOOP)) == 0);

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQ_PROCESS_END),
			VM_KERNEL_UNSLIDE_OR_PERM(kq), 0);

	/*
	 * Return suppressed knotes to their original state.
	 */
	suppressq = kqueue_get_suppressed_queue(kq, NULL);
	while ((kn = TAILQ_FIRST(suppressq)) != NULL) {
		assert(kn->kn_status & KN_SUPPRESSED);
		knote_unsuppress(kn);
	}

	procwait = (kq->kq_state & KQ_PROCWAIT);
	kq->kq_state &= ~(KQ_PROCESSING | KQ_PROCWAIT);

	if (procwait) {
		/* first wake up any thread already waiting to process */
		waitq_wakeup64_all((struct waitq *)&kq->kq_wqs,
		                   CAST_EVENT64_T(suppressq),
		                   THREAD_AWAKENED,
		                   WAITQ_ALL_PRIORITIES);
	}
}