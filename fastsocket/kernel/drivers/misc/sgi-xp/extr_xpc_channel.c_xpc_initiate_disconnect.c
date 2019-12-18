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
struct xpc_partition {struct xpc_channel* channels; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_WDISCONNECT ; 
 int /*<<< orphan*/  XPC_DISCONNECT_CHANNEL (struct xpc_channel*,int /*<<< orphan*/ ,unsigned long*) ; 
 int XPC_MAX_NCHANNELS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xpUnregistering ; 
 short xp_max_npartitions ; 
 int /*<<< orphan*/  xpc_disconnect_wait (int) ; 
 int /*<<< orphan*/  xpc_msgqueue_deref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_msgqueue_ref (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

void
xpc_initiate_disconnect(int ch_number)
{
	unsigned long irq_flags;
	short partid;
	struct xpc_partition *part;
	struct xpc_channel *ch;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	/* initiate the channel disconnect for every active partition */
	for (partid = 0; partid < xp_max_npartitions; partid++) {
		part = &xpc_partitions[partid];

		if (xpc_part_ref(part)) {
			ch = &part->channels[ch_number];
			xpc_msgqueue_ref(ch);

			spin_lock_irqsave(&ch->lock, irq_flags);

			if (!(ch->flags & XPC_C_DISCONNECTED)) {
				ch->flags |= XPC_C_WDISCONNECT;

				XPC_DISCONNECT_CHANNEL(ch, xpUnregistering,
						       &irq_flags);
			}

			spin_unlock_irqrestore(&ch->lock, irq_flags);

			xpc_msgqueue_deref(ch);
			xpc_part_deref(part);
		}
	}

	xpc_disconnect_wait(ch_number);
}