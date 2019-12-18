#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union xpc_channel_ctl_flags {int* flags; int /*<<< orphan*/  all_flags; } ;
typedef  int u32 ;
struct xpc_partition {int nchannels; scalar_t__ act_state; struct xpc_channel* channels; } ;
struct xpc_channel {int flags; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* process_msg_chctl_flags ) (struct xpc_partition*,int) ;int /*<<< orphan*/  (* get_chctl_all_flags ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_CONNECTED ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_OPENREQUEST ; 
 int XPC_C_SETUP ; 
 int XPC_MSG_CHCTL_FLAGS ; 
 int XPC_OPENCLOSE_CHCTL_FLAGS ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_partition*) ; 
 int /*<<< orphan*/  stub2 (struct xpc_partition*,int) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_connect_channel (struct xpc_channel*) ; 
 int /*<<< orphan*/  xpc_process_disconnect (struct xpc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  xpc_process_openclose_chctl_flags (struct xpc_partition*,int,int) ; 

void
xpc_process_sent_chctl_flags(struct xpc_partition *part)
{
	unsigned long irq_flags;
	union xpc_channel_ctl_flags chctl;
	struct xpc_channel *ch;
	int ch_number;
	u32 ch_flags;

	chctl.all_flags = xpc_arch_ops.get_chctl_all_flags(part);

	/*
	 * Initiate channel connections for registered channels.
	 *
	 * For each connected channel that has pending messages activate idle
	 * kthreads and/or create new kthreads as needed.
	 */

	for (ch_number = 0; ch_number < part->nchannels; ch_number++) {
		ch = &part->channels[ch_number];

		/*
		 * Process any open or close related chctl flags, and then deal
		 * with connecting or disconnecting the channel as required.
		 */

		if (chctl.flags[ch_number] & XPC_OPENCLOSE_CHCTL_FLAGS) {
			xpc_process_openclose_chctl_flags(part, ch_number,
							chctl.flags[ch_number]);
		}

		ch_flags = ch->flags;	/* need an atomic snapshot of flags */

		if (ch_flags & XPC_C_DISCONNECTING) {
			spin_lock_irqsave(&ch->lock, irq_flags);
			xpc_process_disconnect(ch, &irq_flags);
			spin_unlock_irqrestore(&ch->lock, irq_flags);
			continue;
		}

		if (part->act_state == XPC_P_AS_DEACTIVATING)
			continue;

		if (!(ch_flags & XPC_C_CONNECTED)) {
			if (!(ch_flags & XPC_C_OPENREQUEST)) {
				DBUG_ON(ch_flags & XPC_C_SETUP);
				(void)xpc_connect_channel(ch);
			}
			continue;
		}

		/*
		 * Process any message related chctl flags, this may involve
		 * the activation of kthreads to deliver any pending messages
		 * sent from the other partition.
		 */

		if (chctl.flags[ch_number] & XPC_MSG_CHCTL_FLAGS)
			xpc_arch_ops.process_msg_chctl_flags(part, ch_number);
	}
}