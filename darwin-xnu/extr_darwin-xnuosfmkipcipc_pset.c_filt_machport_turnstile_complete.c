#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int dummy; } ;
struct knote {struct turnstile* kn_hook; scalar_t__* kn_ext; } ;
typedef  TYPE_1__* ipc_port_t ;
typedef  TYPE_2__* ipc_mqueue_t ;
struct TYPE_13__ {int /*<<< orphan*/  imq_klist; } ;
struct TYPE_12__ {scalar_t__ ip_sync_link_state; struct knote* ip_sync_inheritor_knote; scalar_t__ ip_specialreply; TYPE_2__ ip_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct turnstile* IMQ_INHERITOR (TYPE_2__*) ; 
 int /*<<< orphan*/  IMQ_KLIST_VALID (TYPE_2__*) ; 
 int IPC_PORT_ADJUST_SR_ENABLE_EVENT ; 
 int IPC_PORT_ADJUST_SR_NONE ; 
 scalar_t__ PORT_SYNC_LINK_WORKLOOP_KNOTE ; 
 int /*<<< orphan*/  TURNSTILE_IMMEDIATE_UPDATE ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_NULL ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_HELD ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (struct turnstile*) ; 
 int /*<<< orphan*/  imq_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_port_adjust_special_reply_port_locked (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knote_get_kq (struct knote*) ; 
 struct turnstile* kqueue_turnstile (int /*<<< orphan*/ ) ; 
 struct turnstile* port_send_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,struct turnstile**,struct turnstile**) ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_deallocate_safe (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_reference (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_machport_turnstile_complete(struct knote *kn)
{
	struct turnstile *ts = TURNSTILE_NULL;

	if (kn->kn_ext[3]) {
		ipc_port_t port = (ipc_port_t)kn->kn_ext[3];
		ipc_mqueue_t mqueue = &port->ip_messages;

		ip_lock(port);
		if (port->ip_specialreply) {
			/*
			 * If the reply has been sent to the special reply port already,
			 * then the special reply port may already be reused to do something
			 * entirely different.
			 *
			 * However, the only reason for it to still point to this knote is
			 * that it's still waiting for a reply, so when this is the case,
			 * neuter the linkage.
			 */
			if (port->ip_sync_link_state == PORT_SYNC_LINK_WORKLOOP_KNOTE &&
					port->ip_sync_inheritor_knote == kn) {
				ipc_port_adjust_special_reply_port_locked(port, NULL,
						(IPC_PORT_ADJUST_SR_NONE | IPC_PORT_ADJUST_SR_ENABLE_EVENT), FALSE);
			} else {
				ip_unlock(port);
			}
		} else {
			struct turnstile *kq_ts = kqueue_turnstile(knote_get_kq(kn));

			/*
			 * For receive rights, if their IMQ_INHERITOR() is still this
			 * workloop, then sever the link.
			 *
			 * It has a theoretical hole: if the port is sent again to a new
			 * receive right that is also monitored by the same kqueue,
			 * we would sever the link incorrectly.
			 *
			 * However this would be a REALLY cumbersome thing to do.
			 */
			imq_lock(mqueue);
			if (!IMQ_KLIST_VALID(mqueue) && IMQ_INHERITOR(mqueue) == kq_ts) {
				turnstile_deallocate_safe(kq_ts);
				klist_init(&mqueue->imq_klist);
				ts = port_send_turnstile(port);
			}
			if (ts) {
				turnstile_update_inheritor(ts, TURNSTILE_INHERITOR_NULL,
						TURNSTILE_IMMEDIATE_UPDATE);
				turnstile_reference(ts);
			}
			imq_unlock(mqueue);
			ip_unlock(port);

			if (ts) {
				turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_NOT_HELD);
				turnstile_deallocate(ts);
			}
		}

		ip_release(port);
		kn->kn_ext[3] = 0;
	}

	if (kn->kn_hook) {
		ts = kn->kn_hook;

		turnstile_update_inheritor(ts, TURNSTILE_INHERITOR_NULL,
				TURNSTILE_IMMEDIATE_UPDATE);
		turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_HELD);

		turnstile_complete((uintptr_t)kn, (struct turnstile **)&kn->kn_hook, &ts);
		turnstile_cleanup();

		assert(ts);
		turnstile_deallocate(ts);
	}
}