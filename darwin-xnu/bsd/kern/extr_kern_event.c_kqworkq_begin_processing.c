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
struct kqworkq {int dummy; } ;
struct kqrequest {int /*<<< orphan*/  kqr_state; int /*<<< orphan*/  kqr_thread; int /*<<< orphan*/  kqr_qos_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_KEVENT_KQWQ_PROCESS_BEGIN ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KDBG_FILTERED (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEV_EVTID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KQWQAE_BEGIN_PROCESSING ; 
 int kqworkq_acknowledge_events (struct kqworkq*,struct kqrequest*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kqworkq_begin_processing(struct kqworkq *kqwq, struct kqrequest *kqr,
		int kevent_flags)
{
	int rc = 0;

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWQ_PROCESS_BEGIN) | DBG_FUNC_START,
			0, kqr->kqr_qos_index);

	rc = kqworkq_acknowledge_events(kqwq, kqr, kevent_flags,
			KQWQAE_BEGIN_PROCESSING);

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWQ_PROCESS_BEGIN) | DBG_FUNC_END,
			thread_tid(kqr->kqr_thread), kqr->kqr_state);

	return rc;
}