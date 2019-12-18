#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_mqueue; } ;
struct knote {int kn_flags; TYPE_1__ kn_ptr; } ;
typedef  TYPE_2__* ipc_mqueue_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_t ;
struct TYPE_7__ {int /*<<< orphan*/  imq_messages; } ;

/* Variables and functions */
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int FILTER_ACTIVE ; 
 int FILTER_RESET_EVENT_QOS ; 
 int /*<<< orphan*/  IKM_NULL ; 
 long NOTE_REVOKE ; 
 int /*<<< orphan*/  assert (int) ; 
 int filt_machport_adjust_qos (struct knote*,int /*<<< orphan*/ ) ; 
 int imq_held (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_is_set (TYPE_2__*) ; 
 scalar_t__ imq_is_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
filt_machportevent(
	struct knote *kn,
	long hint)
{
	ipc_mqueue_t mqueue = kn->kn_ptr.p_mqueue;
	ipc_kmsg_t first;
	int result = 0;

	/* mqueue locked by caller */
	assert(imq_held(mqueue));

	if (hint == NOTE_REVOKE) {
		kn->kn_flags |= EV_EOF | EV_ONESHOT;
		result = FILTER_ACTIVE | FILTER_RESET_EVENT_QOS;
	} else if (imq_is_valid(mqueue)) {
		assert(!imq_is_set(mqueue));
		if ((first = ipc_kmsg_queue_first(&mqueue->imq_messages)) != IKM_NULL) {
			result = FILTER_ACTIVE | filt_machport_adjust_qos(kn, first);
		}
	}

	return result;
}