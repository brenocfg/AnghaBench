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
struct waitq {int dummy; } ;
struct kqworkq {int dummy; } ;
struct kqworkloop {int dummy; } ;
struct kqueue {int kq_state; int /*<<< orphan*/  kq_wqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct kqfile {TYPE_1__ kqf_sel; } ;
struct knote {int /*<<< orphan*/  kn_qos_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KQ_EVENT ; 
 int KQ_PROCESSING ; 
 int KQ_SEL ; 
 int KQ_SLEEP ; 
 int KQ_WAKEUP ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 int /*<<< orphan*/  kqworkloop_is_processing_on_current_thread (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqworkloop_request_help (struct kqworkloop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqworkq_request_help (struct kqworkq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_wakeup64_all (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
knote_wakeup(struct knote *kn)
{
	struct kqueue *kq = knote_get_kq(kn);

	kqlock_held(kq);

	if (kq->kq_state & KQ_WORKQ) {
		struct kqworkq *kqwq = (struct kqworkq *)kq;

		kqworkq_request_help(kqwq, kn->kn_qos_index);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;

		/*
		 * kqworkloop_end_processing() will perform the required QoS
		 * computations when it unsets the processing mode.
		 */
		if (!kqworkloop_is_processing_on_current_thread(kqwl)) {
			kqworkloop_request_help(kqwl, kn->kn_qos_index);
		}
	} else {
		struct kqfile *kqf = (struct kqfile *)kq;

		/* flag wakeups during processing */
		if (kq->kq_state & KQ_PROCESSING)
			kq->kq_state |= KQ_WAKEUP;

		/* wakeup a thread waiting on this queue */
		if (kq->kq_state & (KQ_SLEEP | KQ_SEL)) {
			kq->kq_state &= ~(KQ_SLEEP | KQ_SEL);
			waitq_wakeup64_all((struct waitq *)&kq->kq_wqs, KQ_EVENT,
					THREAD_AWAKENED, WAITQ_ALL_PRIORITIES);
		}

		/* wakeup other kqueues/select sets we're inside */
		KNOTE(&kqf->kqf_sel.si_note, 0);
	}
}