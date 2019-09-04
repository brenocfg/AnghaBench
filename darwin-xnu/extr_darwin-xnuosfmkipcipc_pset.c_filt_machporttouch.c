#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_mqueue; } ;
struct knote {int kn_sfflags; int /*<<< orphan*/ * kn_ext; TYPE_1__ kn_ptr; } ;
struct kevent_internal_s {int fflags; int flags; int /*<<< orphan*/ * ext; } ;
typedef  TYPE_2__* ipc_mqueue_t ;
typedef  int /*<<< orphan*/  ipc_kmsg_t ;
struct TYPE_8__ {int /*<<< orphan*/  imq_messages; } ;

/* Variables and functions */
 int EV_ENABLE ; 
 int FILTER_ACTIVE ; 
 int FILTER_RESET_EVENT_QOS ; 
 int /*<<< orphan*/  IKM_NULL ; 
 int MACH_RCV_MSG ; 
 int filt_machport_adjust_qos (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filt_machport_turnstile_complete (struct knote*) ; 
 int /*<<< orphan*/  imq_is_set (TYPE_2__*) ; 
 scalar_t__ imq_is_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
filt_machporttouch(
	struct knote *kn,
	struct kevent_internal_s *kev)
{
	ipc_mqueue_t mqueue = kn->kn_ptr.p_mqueue;
	ipc_kmsg_t first;
	int result = 0;

	/* copy in new settings and save off new input fflags */
	kn->kn_sfflags = kev->fflags;
	kn->kn_ext[0] = kev->ext[0];
	kn->kn_ext[1] = kev->ext[1];

	if (kev->flags & EV_ENABLE) {
		/*
		 * If the knote is being enabled, make sure there's no lingering
		 * IPC overrides from the previous message delivery.
		 */
		filt_machport_turnstile_complete(kn);
	}

	/*
	 * If the mqueue is a valid port and there is a message
	 * that will be direct-received from the knote, update
	 * the knote qos based on the first message and trigger
	 * the event. If there are no more messages, reset the
	 * QoS to the value provided by the kevent.
	 */
	imq_lock(mqueue);
	if (imq_is_valid(mqueue) && !imq_is_set(mqueue) &&
	    (first = ipc_kmsg_queue_first(&mqueue->imq_messages)) != IKM_NULL) {
		result = FILTER_ACTIVE | filt_machport_adjust_qos(kn, first);
	} else if (kn->kn_sfflags & MACH_RCV_MSG) {
		result = FILTER_RESET_EVENT_QOS;
	}
	imq_unlock(mqueue);

	return result;
}