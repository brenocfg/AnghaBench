#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct xpc_msg_sn2 {int flags; } ;
struct TYPE_5__ {int get; } ;
struct xpc_channel_sn2 {TYPE_3__* local_GP; scalar_t__ remote_msgqueue; TYPE_2__ w_local_GP; } ;
struct TYPE_4__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int remote_nentries; int entry_size; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; TYPE_1__ sn; } ;
typedef  int s64 ;
struct TYPE_6__ {int get; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_M_SN2_DONE ; 
 int XPC_M_SN2_INTERRUPT ; 
 int cmpxchg_rel (int*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_send_chctl_msgrequest_sn2 (struct xpc_channel*) ; 

__attribute__((used)) static void
xpc_acknowledge_msgs_sn2(struct xpc_channel *ch, s64 initial_get, u8 msg_flags)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	struct xpc_msg_sn2 *msg;
	s64 get = initial_get + 1;
	int send_msgrequest = 0;

	while (1) {

		while (1) {
			if (get == ch_sn2->w_local_GP.get)
				break;

			msg = (struct xpc_msg_sn2 *)((u64)ch_sn2->
						     remote_msgqueue + (get %
						     ch->remote_nentries) *
						     ch->entry_size);

			if (!(msg->flags & XPC_M_SN2_DONE))
				break;

			msg_flags |= msg->flags;
			get++;
		}

		if (get == initial_get) {
			/* nothing's changed */
			break;
		}

		if (cmpxchg_rel(&ch_sn2->local_GP->get, initial_get, get) !=
		    initial_get) {
			/* someone else beat us to it */
			DBUG_ON(ch_sn2->local_GP->get <= initial_get);
			break;
		}

		/* we just set the new value of local_GP->get */

		dev_dbg(xpc_chan, "local_GP->get changed to %lld, partid=%d, "
			"channel=%d\n", get, ch->partid, ch->number);

		send_msgrequest = (msg_flags & XPC_M_SN2_INTERRUPT);

		/*
		 * We need to ensure that the message referenced by
		 * local_GP->get is not XPC_M_SN2_DONE or that local_GP->get
		 * equals w_local_GP.get, so we'll go have a look.
		 */
		initial_get = get;
	}

	if (send_msgrequest)
		xpc_send_chctl_msgrequest_sn2(ch);
}