#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uthread {struct kqrequest* uu_kqr_bound; } ;
struct kqueue {int kq_state; struct kqtailq* kq_queue; } ;
struct kqtailq {int dummy; } ;
struct kqrequest {int kqr_state; size_t kqr_qos_index; } ;
struct knote {int dummy; } ;
struct filt_process_s {unsigned int fp_flags; } ;
struct TYPE_6__ {TYPE_4__* kqwl; TYPE_2__* kqwq; struct kqueue* kq; } ;
typedef  TYPE_1__ kqueue_t ;
typedef  int /*<<< orphan*/  kevent_callback_t ;
struct TYPE_8__ {struct kqtailq* kqwl_queue; struct kqrequest kqwl_request; } ;
struct TYPE_7__ {struct kqtailq* kqwq_queue; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int EWOULDBLOCK ; 
 unsigned int KEVENT_FLAG_PARKING ; 
 int KQR_WORKLOOP ; 
 int KQWL_NBUCKETS ; 
 int /*<<< orphan*/  KQ_PROCESSING ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 size_t QOS_INDEX_KQFILE ; 
 struct knote* TAILQ_FIRST (struct kqtailq*) ; 
 int /*<<< orphan*/  assert (unsigned int) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int knote_process (struct knote*,int /*<<< orphan*/ ,void*,struct filt_process_s*) ; 
 int kqfile_begin_processing (struct kqueue*) ; 
 int /*<<< orphan*/  kqfile_end_processing (struct kqueue*) ; 
 int kqworkloop_begin_processing (TYPE_4__*,unsigned int) ; 
 int kqworkloop_end_processing (TYPE_4__*,int /*<<< orphan*/ ,unsigned int) ; 
 int kqworkq_begin_processing (TYPE_2__*,struct kqrequest*,unsigned int) ; 
 int kqworkq_end_processing (TYPE_2__*,struct kqrequest*,unsigned int) ; 
 int /*<<< orphan*/  panic (char*,struct kqueue*,int) ; 

__attribute__((used)) static int
kqueue_process(struct kqueue *kq,
		kevent_callback_t callback,
		void *callback_data,
		struct filt_process_s *process_data,
		int *countp)
{
	struct uthread *ut = get_bsdthread_info(current_thread());
	struct kqrequest *kqr = ut->uu_kqr_bound;
	struct knote *kn;
	unsigned int flags = process_data ? process_data->fp_flags : 0;
	int nevents = 0, error = 0, rc = 0;
	struct kqtailq *base_queue, *queue;
	kqueue_t kqu = { .kq = kq };
#if DEBUG || DEVELOPMENT
	int retries = 64;
#endif

	if (kq->kq_state & KQ_WORKQ) {
		if (kqr == NULL || (kqr->kqr_state & KQR_WORKLOOP)) {
			return EJUSTRETURN;
		}
		rc = kqworkq_begin_processing(kqu.kqwq, kqr, flags);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		if (ut->uu_kqr_bound != &kqu.kqwl->kqwl_request) {
			return EJUSTRETURN;
		}
		rc = kqworkloop_begin_processing(kqu.kqwl, flags);
	} else {
		rc = kqfile_begin_processing(kq);
	}

	if (rc == -1) {
		/* Nothing to process */
		*countp = 0;
		return 0;
	}

	/*
	 * loop through the enqueued knotes associated with this request,
	 * processing each one. Each request may have several queues
	 * of knotes to process (depending on the type of kqueue) so we
	 * have to loop through all the queues as long as we have additional
	 * space.
	 */

process_again:
	if (kq->kq_state & KQ_WORKQ) {
		base_queue = queue = &kqu.kqwq->kqwq_queue[kqr->kqr_qos_index];
	} else if (kq->kq_state & KQ_WORKLOOP) {
		base_queue = &kqu.kqwl->kqwl_queue[0];
		queue = &kqu.kqwl->kqwl_queue[KQWL_NBUCKETS - 1];
	} else {
		base_queue = queue = &kq->kq_queue[QOS_INDEX_KQFILE];
	}

	do {
		while (error == 0 && (kn = TAILQ_FIRST(queue)) != NULL) {
			error = knote_process(kn, callback, callback_data, process_data);
			if (error == EJUSTRETURN) {
				error = 0;
			} else {
				nevents++;
			}
			/* error is EWOULDBLOCK when the out event array is full */
		}

		if (error == EWOULDBLOCK) {
			/* break out if no more space for additional events */
			error = 0;
			break;
		}
	} while (queue-- > base_queue);

	*countp = nevents;

	/*
	 * If KEVENT_FLAG_PARKING is set, and no kevents have been returned,
	 * we want to unbind the kqrequest from the thread.
	 *
	 * However, because the kq locks are dropped several times during process,
	 * new knotes may have fired again, in which case, we want to fail the end
	 * processing and process again, until it converges.
	 *
	 * If we returned events however, end processing never fails.
	 */
	if (error || nevents) flags &= ~KEVENT_FLAG_PARKING;
	if (kq->kq_state & KQ_WORKQ) {
		rc = kqworkq_end_processing(kqu.kqwq, kqr, flags);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		rc = kqworkloop_end_processing(kqu.kqwl, KQ_PROCESSING, flags);
	} else {
		kqfile_end_processing(kq);
		rc = 0;
	}
	if (rc == -1) {
		assert(flags & KEVENT_FLAG_PARKING);
#if DEBUG || DEVELOPMENT
		if (retries-- == 0) {
			panic("kevent: way too many knote_process retries, kq: %p (0x%02x)",
					kq, kq->kq_state);
		}
#endif
		goto process_again;
	}
	return error;
}