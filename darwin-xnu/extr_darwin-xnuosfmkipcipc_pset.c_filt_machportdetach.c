#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
struct TYPE_9__ {TYPE_2__* p_mqueue; } ;
struct knote {int kn_status; int kn_flags; TYPE_1__ kn_ptr; } ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_mqueue_t ;
struct TYPE_10__ {int /*<<< orphan*/  imq_wait_queue; int /*<<< orphan*/  imq_klist; } ;

/* Variables and functions */
 int EV_EOF ; 
 int /*<<< orphan*/  IMQ_KLIST_VALID (TYPE_2__*) ; 
 TYPE_2__* IMQ_NULL ; 
 scalar_t__ IOT_PORT ; 
 scalar_t__ IOT_PORT_SET ; 
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int KN_VANISHED ; 
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filt_machport_turnstile_complete (struct knote*) ; 
 int /*<<< orphan*/  imq_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_2__*) ; 
 scalar_t__ io_otype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_from_mq (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_port_get_inheritor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knote_unlink_waitq (struct knote*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqueue_to_object (TYPE_2__*) ; 
 struct turnstile* port_send_turnstile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_reference (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_machportdetach(
	struct knote *kn)
{
	ipc_mqueue_t mqueue = kn->kn_ptr.p_mqueue;
	ipc_object_t object = mqueue_to_object(mqueue);
	struct turnstile *send_turnstile = TURNSTILE_NULL;

	filt_machport_turnstile_complete(kn);

	imq_lock(mqueue);
	if ((kn->kn_status & KN_VANISHED) || (kn->kn_flags & EV_EOF)) {
		/*
		 * ipc_mqueue_changed() already unhooked this knote from the mqueue,
		 */
	} else {
		assert(IMQ_KLIST_VALID(mqueue));
		KNOTE_DETACH(&mqueue->imq_klist, kn);
	}

	if (io_otype(object) == IOT_PORT) {
		ipc_port_t port = ip_from_mq(mqueue);

		send_turnstile = port_send_turnstile(port);
		if (send_turnstile) {
			turnstile_reference(send_turnstile);
			turnstile_update_inheritor(send_turnstile,
				ipc_port_get_inheritor(port),
				TURNSTILE_INHERITOR_TURNSTILE | TURNSTILE_IMMEDIATE_UPDATE);
		}
	}

	/* Clear the knote pointer once the knote has been removed from turnstile */
	kn->kn_ptr.p_mqueue = IMQ_NULL;
	imq_unlock(mqueue);

	if (send_turnstile) {
		turnstile_update_inheritor_complete(send_turnstile,
				TURNSTILE_INTERLOCK_NOT_HELD);
		turnstile_deallocate(send_turnstile);
	}

	if (io_otype(object) == IOT_PORT_SET) {
		/*
		 * Unlink the portset wait queue from knote/kqueue.
		 * JMM - Does this need to be atomic under the mq lock?
		 */
		(void)knote_unlink_waitq(kn, &mqueue->imq_wait_queue);
	}
	io_release(object);
}