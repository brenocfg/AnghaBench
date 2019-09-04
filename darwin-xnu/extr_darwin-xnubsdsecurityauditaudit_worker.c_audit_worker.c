#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_continue_t ;
struct kaudit_record {int k_ar_commit; } ;
struct kaudit_queue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vc_thread; } ;
struct TYPE_3__ {scalar_t__ aq_lowater; } ;

/* Variables and functions */
 int AR_DRAIN_QUEUE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ TAILQ_EMPTY (struct kaudit_queue*) ; 
 struct kaudit_record* TAILQ_FIRST (struct kaudit_queue*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct kaudit_queue*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct kaudit_queue*,struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct kaudit_queue*,struct kaudit_record*,int /*<<< orphan*/ ) ; 
 TYPE_2__ audit_ctx ; 
 int /*<<< orphan*/  audit_drain_cv ; 
 int /*<<< orphan*/  audit_free (struct kaudit_record*) ; 
 int /*<<< orphan*/  audit_mtx ; 
 struct kaudit_queue audit_q ; 
 scalar_t__ audit_q_draining ; 
 scalar_t__ audit_q_len ; 
 TYPE_1__ audit_qctrl ; 
 int /*<<< orphan*/  audit_watermark_cv ; 
 int /*<<< orphan*/  audit_worker_cv ; 
 int /*<<< orphan*/  audit_worker_process_record (struct kaudit_record*) ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait_continuation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_q ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) __attribute__((noreturn))
static void
audit_worker(void)
{
	struct kaudit_queue ar_worklist;
	struct kaudit_record *ar;
	int lowater_signal;

	if (audit_ctx.vc_thread == NULL)
		audit_ctx.vc_thread = current_thread();

	TAILQ_INIT(&ar_worklist);
	mtx_lock(&audit_mtx);
	while (1) {
		mtx_assert(&audit_mtx, MA_OWNED);

		/*
		 * Wait for a record.
		 */
		while (TAILQ_EMPTY(&audit_q))
			cv_wait_continuation(&audit_worker_cv, &audit_mtx,
			    (thread_continue_t)audit_worker);

		/*
		 * If there are records in the global audit record queue,
		 * transfer them to a thread-local queue and process them
		 * one by one.  If we cross the low watermark threshold,
		 * signal any waiting processes that they may wake up and
		 * continue generating records.
		 */
		lowater_signal = 0;
		while ((ar = TAILQ_FIRST(&audit_q))) {
			TAILQ_REMOVE(&audit_q, ar, k_q);
			audit_q_len--;
			if (audit_q_len == audit_qctrl.aq_lowater)
				lowater_signal++;
			TAILQ_INSERT_TAIL(&ar_worklist, ar, k_q);
		}
		if (lowater_signal)
			cv_broadcast(&audit_watermark_cv);

		mtx_unlock(&audit_mtx);
		while ((ar = TAILQ_FIRST(&ar_worklist))) {
			TAILQ_REMOVE(&ar_worklist, ar, k_q);
			if (ar->k_ar_commit & AR_DRAIN_QUEUE) {
				audit_q_draining = 0;
				cv_broadcast(&audit_drain_cv);
			} else {
				audit_worker_process_record(ar);
				audit_free(ar);
			}
		}
		mtx_lock(&audit_mtx);
	}
}