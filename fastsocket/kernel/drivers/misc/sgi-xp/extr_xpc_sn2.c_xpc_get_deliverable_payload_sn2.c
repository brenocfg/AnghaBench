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
struct xpc_msg_sn2 {scalar_t__ number; int flags; int /*<<< orphan*/  payload; } ;
struct TYPE_6__ {scalar_t__ get; } ;
struct TYPE_5__ {scalar_t__ put; } ;
struct xpc_channel_sn2 {TYPE_3__ w_local_GP; TYPE_2__ w_remote_GP; } ;
struct TYPE_4__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; TYPE_1__ sn; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_M_SN2_DONE ; 
 int XPC_M_SN2_READY ; 
 scalar_t__ cmpxchg (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  xpc_chan ; 
 struct xpc_msg_sn2* xpc_pull_remote_msg_sn2 (struct xpc_channel*,scalar_t__) ; 

__attribute__((used)) static void *
xpc_get_deliverable_payload_sn2(struct xpc_channel *ch)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	struct xpc_msg_sn2 *msg;
	void *payload = NULL;
	s64 get;

	do {
		if (ch->flags & XPC_C_DISCONNECTING)
			break;

		get = ch_sn2->w_local_GP.get;
		smp_rmb();	/* guarantee that .get loads before .put */
		if (get == ch_sn2->w_remote_GP.put)
			break;

		/* There are messages waiting to be pulled and delivered.
		 * We need to try to secure one for ourselves. We'll do this
		 * by trying to increment w_local_GP.get and hope that no one
		 * else beats us to it. If they do, we'll we'll simply have
		 * to try again for the next one.
		 */

		if (cmpxchg(&ch_sn2->w_local_GP.get, get, get + 1) == get) {
			/* we got the entry referenced by get */

			dev_dbg(xpc_chan, "w_local_GP.get changed to %lld, "
				"partid=%d, channel=%d\n", get + 1,
				ch->partid, ch->number);

			/* pull the message from the remote partition */

			msg = xpc_pull_remote_msg_sn2(ch, get);

			if (msg != NULL) {
				DBUG_ON(msg->number != get);
				DBUG_ON(msg->flags & XPC_M_SN2_DONE);
				DBUG_ON(!(msg->flags & XPC_M_SN2_READY));

				payload = &msg->payload;
			}
			break;
		}

	} while (1);

	return payload;
}