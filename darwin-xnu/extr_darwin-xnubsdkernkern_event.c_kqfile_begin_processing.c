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

/* Variables and functions */
 int /*<<< orphan*/  BSD_KEVENT_KQ_PROCESS_BEGIN ; 
 int /*<<< orphan*/  CAST_EVENT64_T (struct kqtailq*) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KDBG_FILTERED (int,int /*<<< orphan*/ ,...) ; 
 int KEV_EVTID (int /*<<< orphan*/ ) ; 
 int KQ_DRAIN ; 
 int KQ_PROCESSING ; 
 int KQ_PROCWAIT ; 
 int KQ_WAKEUP ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  QOS_INDEX_KQFILE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int THREAD_UNINT ; 
 int THREAD_WAIT_NOREPORT ; 
 int /*<<< orphan*/  TIMEOUT_WAIT_FOREVER ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (struct kqueue*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 struct kqtailq* kqueue_get_suppressed_queue (struct kqueue*,int /*<<< orphan*/ *) ; 
 scalar_t__ kqueue_queue_empty (struct kqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_assert_wait64 (struct waitq*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_set_clear_preposts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kqfile_begin_processing(struct kqueue *kq)
{
	struct kqtailq *suppressq;

	kqlock_held(kq);

	assert((kq->kq_state & (KQ_WORKQ | KQ_WORKLOOP)) == 0);
	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQ_PROCESS_BEGIN) | DBG_FUNC_START,
	              VM_KERNEL_UNSLIDE_OR_PERM(kq), 0);

	/* wait to become the exclusive processing thread */
	for (;;) {
		if (kq->kq_state & KQ_DRAIN) {
			KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQ_PROCESS_BEGIN) | DBG_FUNC_END,
			              VM_KERNEL_UNSLIDE_OR_PERM(kq), 2);
			return -1;
		}

		if ((kq->kq_state & KQ_PROCESSING) == 0)
			break;

		/* if someone else is processing the queue, wait */
		kq->kq_state |= KQ_PROCWAIT;
		suppressq = kqueue_get_suppressed_queue(kq, NULL);
		waitq_assert_wait64((struct waitq *)&kq->kq_wqs,
				CAST_EVENT64_T(suppressq), THREAD_UNINT | THREAD_WAIT_NOREPORT,
				TIMEOUT_WAIT_FOREVER);

		kqunlock(kq);
		thread_block(THREAD_CONTINUE_NULL);
		kqlock(kq);
	}

	/* Nobody else processing */

	/* clear pre-posts and KQ_WAKEUP now, in case we bail early */
	waitq_set_clear_preposts(&kq->kq_wqs);
	kq->kq_state &= ~KQ_WAKEUP;

	/* anything left to process? */
	if (kqueue_queue_empty(kq, QOS_INDEX_KQFILE)) {
		KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQ_PROCESS_BEGIN) | DBG_FUNC_END,
		              VM_KERNEL_UNSLIDE_OR_PERM(kq), 1);
		return -1;
	}

	/* convert to processing mode */
	kq->kq_state |= KQ_PROCESSING;

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQ_PROCESS_BEGIN) | DBG_FUNC_END,
	              VM_KERNEL_UNSLIDE_OR_PERM(kq));

	return 0;
}