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
struct xpc_send_msg_slot_uv {int /*<<< orphan*/ * func; } ;
struct TYPE_3__ {struct xpc_send_msg_slot_uv* send_msg_slots; } ;
struct TYPE_4__ {TYPE_1__ uv; } ;
struct xpc_channel {int flags; int local_nentries; int /*<<< orphan*/  reason; TYPE_2__ sn; int /*<<< orphan*/  n_to_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_DISCONNECTING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_notify_sender_uv (struct xpc_channel*,struct xpc_send_msg_slot_uv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_notify_senders_of_disconnect_uv(struct xpc_channel *ch)
{
	struct xpc_send_msg_slot_uv *msg_slot;
	int entry;

	DBUG_ON(!(ch->flags & XPC_C_DISCONNECTING));

	for (entry = 0; entry < ch->local_nentries; entry++) {

		if (atomic_read(&ch->n_to_notify) == 0)
			break;

		msg_slot = &ch->sn.uv.send_msg_slots[entry];
		if (msg_slot->func != NULL)
			xpc_notify_sender_uv(ch, msg_slot, ch->reason);
	}
}