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
typedef  int u8 ;
struct TYPE_3__ {int* flags; } ;
struct xpc_partition {scalar_t__ act_state; int /*<<< orphan*/  nchannels_active; int /*<<< orphan*/  chctl_lock; TYPE_1__ chctl; struct xpc_channel* channels; struct xpc_openclose_args* remote_openclose_args; } ;
struct xpc_openclose_args {int reason; scalar_t__ entry_size; scalar_t__ local_nentries; scalar_t__ local_msgqueue_pa; scalar_t__ remote_nentries; } ;
struct xpc_channel {int flags; int delayed_chctl_flags; scalar_t__ remote_nentries; scalar_t__ entry_size; scalar_t__ local_nentries; int /*<<< orphan*/  lock; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_4__ {int (* save_remote_msgqueue_pa ) (struct xpc_channel*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_CHCTL_CLOSEREPLY ; 
 int XPC_CHCTL_CLOSEREQUEST ; 
 int XPC_CHCTL_OPENCOMPLETE ; 
 int XPC_CHCTL_OPENREPLY ; 
 int XPC_CHCTL_OPENREQUEST ; 
 int XPC_C_CLOSEREPLY ; 
 int XPC_C_CLOSEREQUEST ; 
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTING ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_OPENREPLY ; 
 int XPC_C_OPENREQUEST ; 
 int XPC_C_RCLOSEREPLY ; 
 int XPC_C_RCLOSEREQUEST ; 
 int XPC_C_ROPENCOMPLETE ; 
 int XPC_C_ROPENREPLY ; 
 int XPC_C_ROPENREQUEST ; 
 int XPC_C_WDISCONNECT ; 
 int /*<<< orphan*/  XPC_DISCONNECT_CHANNEL (struct xpc_channel*,int,unsigned long*) ; 
 scalar_t__ XPC_P_AS_DEACTIVATING ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct xpc_channel*,scalar_t__) ; 
 int xpOpenCloseError ; 
 int xpOtherUnregistering ; 
 int xpSuccess ; 
 int xpUnequalMsgSizes ; 
 int xpUnknownReason ; 
 int xpUnregistering ; 
 TYPE_2__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_create_kthreads (struct xpc_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_process_connect (struct xpc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  xpc_process_disconnect (struct xpc_channel*,unsigned long*) ; 

__attribute__((used)) static void
xpc_process_openclose_chctl_flags(struct xpc_partition *part, int ch_number,
				  u8 chctl_flags)
{
	unsigned long irq_flags;
	struct xpc_openclose_args *args =
	    &part->remote_openclose_args[ch_number];
	struct xpc_channel *ch = &part->channels[ch_number];
	enum xp_retval reason;
	enum xp_retval ret;
	int create_kthread = 0;

	spin_lock_irqsave(&ch->lock, irq_flags);

again:

	if ((ch->flags & XPC_C_DISCONNECTED) &&
	    (ch->flags & XPC_C_WDISCONNECT)) {
		/*
		 * Delay processing chctl flags until thread waiting disconnect
		 * has had a chance to see that the channel is disconnected.
		 */
		ch->delayed_chctl_flags |= chctl_flags;
		goto out;
	}

	if (chctl_flags & XPC_CHCTL_CLOSEREQUEST) {

		dev_dbg(xpc_chan, "XPC_CHCTL_CLOSEREQUEST (reason=%d) received "
			"from partid=%d, channel=%d\n", args->reason,
			ch->partid, ch->number);

		/*
		 * If RCLOSEREQUEST is set, we're probably waiting for
		 * RCLOSEREPLY. We should find it and a ROPENREQUEST packed
		 * with this RCLOSEREQUEST in the chctl_flags.
		 */

		if (ch->flags & XPC_C_RCLOSEREQUEST) {
			DBUG_ON(!(ch->flags & XPC_C_DISCONNECTING));
			DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));
			DBUG_ON(!(ch->flags & XPC_C_CLOSEREPLY));
			DBUG_ON(ch->flags & XPC_C_RCLOSEREPLY);

			DBUG_ON(!(chctl_flags & XPC_CHCTL_CLOSEREPLY));
			chctl_flags &= ~XPC_CHCTL_CLOSEREPLY;
			ch->flags |= XPC_C_RCLOSEREPLY;

			/* both sides have finished disconnecting */
			xpc_process_disconnect(ch, &irq_flags);
			DBUG_ON(!(ch->flags & XPC_C_DISCONNECTED));
			goto again;
		}

		if (ch->flags & XPC_C_DISCONNECTED) {
			if (!(chctl_flags & XPC_CHCTL_OPENREQUEST)) {
				if (part->chctl.flags[ch_number] &
				    XPC_CHCTL_OPENREQUEST) {

					DBUG_ON(ch->delayed_chctl_flags != 0);
					spin_lock(&part->chctl_lock);
					part->chctl.flags[ch_number] |=
					    XPC_CHCTL_CLOSEREQUEST;
					spin_unlock(&part->chctl_lock);
				}
				goto out;
			}

			XPC_SET_REASON(ch, 0, 0);
			ch->flags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&part->nchannels_active);
			ch->flags |= (XPC_C_CONNECTING | XPC_C_ROPENREQUEST);
		}

		chctl_flags &= ~(XPC_CHCTL_OPENREQUEST | XPC_CHCTL_OPENREPLY |
		    XPC_CHCTL_OPENCOMPLETE);

		/*
		 * The meaningful CLOSEREQUEST connection state fields are:
		 *      reason = reason connection is to be closed
		 */

		ch->flags |= XPC_C_RCLOSEREQUEST;

		if (!(ch->flags & XPC_C_DISCONNECTING)) {
			reason = args->reason;
			if (reason <= xpSuccess || reason > xpUnknownReason)
				reason = xpUnknownReason;
			else if (reason == xpUnregistering)
				reason = xpOtherUnregistering;

			XPC_DISCONNECT_CHANNEL(ch, reason, &irq_flags);

			DBUG_ON(chctl_flags & XPC_CHCTL_CLOSEREPLY);
			goto out;
		}

		xpc_process_disconnect(ch, &irq_flags);
	}

	if (chctl_flags & XPC_CHCTL_CLOSEREPLY) {

		dev_dbg(xpc_chan, "XPC_CHCTL_CLOSEREPLY received from partid="
			"%d, channel=%d\n", ch->partid, ch->number);

		if (ch->flags & XPC_C_DISCONNECTED) {
			DBUG_ON(part->act_state != XPC_P_AS_DEACTIVATING);
			goto out;
		}

		DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));

		if (!(ch->flags & XPC_C_RCLOSEREQUEST)) {
			if (part->chctl.flags[ch_number] &
			    XPC_CHCTL_CLOSEREQUEST) {

				DBUG_ON(ch->delayed_chctl_flags != 0);
				spin_lock(&part->chctl_lock);
				part->chctl.flags[ch_number] |=
				    XPC_CHCTL_CLOSEREPLY;
				spin_unlock(&part->chctl_lock);
			}
			goto out;
		}

		ch->flags |= XPC_C_RCLOSEREPLY;

		if (ch->flags & XPC_C_CLOSEREPLY) {
			/* both sides have finished disconnecting */
			xpc_process_disconnect(ch, &irq_flags);
		}
	}

	if (chctl_flags & XPC_CHCTL_OPENREQUEST) {

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENREQUEST (entry_size=%d, "
			"local_nentries=%d) received from partid=%d, "
			"channel=%d\n", args->entry_size, args->local_nentries,
			ch->partid, ch->number);

		if (part->act_state == XPC_P_AS_DEACTIVATING ||
		    (ch->flags & XPC_C_ROPENREQUEST)) {
			goto out;
		}

		if (ch->flags & (XPC_C_DISCONNECTING | XPC_C_WDISCONNECT)) {
			ch->delayed_chctl_flags |= XPC_CHCTL_OPENREQUEST;
			goto out;
		}
		DBUG_ON(!(ch->flags & (XPC_C_DISCONNECTED |
				       XPC_C_OPENREQUEST)));
		DBUG_ON(ch->flags & (XPC_C_ROPENREQUEST | XPC_C_ROPENREPLY |
				     XPC_C_OPENREPLY | XPC_C_CONNECTED));

		/*
		 * The meaningful OPENREQUEST connection state fields are:
		 *      entry_size = size of channel's messages in bytes
		 *      local_nentries = remote partition's local_nentries
		 */
		if (args->entry_size == 0 || args->local_nentries == 0) {
			/* assume OPENREQUEST was delayed by mistake */
			goto out;
		}

		ch->flags |= (XPC_C_ROPENREQUEST | XPC_C_CONNECTING);
		ch->remote_nentries = args->local_nentries;

		if (ch->flags & XPC_C_OPENREQUEST) {
			if (args->entry_size != ch->entry_size) {
				XPC_DISCONNECT_CHANNEL(ch, xpUnequalMsgSizes,
						       &irq_flags);
				goto out;
			}
		} else {
			ch->entry_size = args->entry_size;

			XPC_SET_REASON(ch, 0, 0);
			ch->flags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&part->nchannels_active);
		}

		xpc_process_connect(ch, &irq_flags);
	}

	if (chctl_flags & XPC_CHCTL_OPENREPLY) {

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY (local_msgqueue_pa="
			"0x%lx, local_nentries=%d, remote_nentries=%d) "
			"received from partid=%d, channel=%d\n",
			args->local_msgqueue_pa, args->local_nentries,
			args->remote_nentries, ch->partid, ch->number);

		if (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			goto out;

		if (!(ch->flags & XPC_C_OPENREQUEST)) {
			XPC_DISCONNECT_CHANNEL(ch, xpOpenCloseError,
					       &irq_flags);
			goto out;
		}

		DBUG_ON(!(ch->flags & XPC_C_ROPENREQUEST));
		DBUG_ON(ch->flags & XPC_C_CONNECTED);

		/*
		 * The meaningful OPENREPLY connection state fields are:
		 *      local_msgqueue_pa = physical address of remote
		 *                          partition's local_msgqueue
		 *      local_nentries = remote partition's local_nentries
		 *      remote_nentries = remote partition's remote_nentries
		 */
		DBUG_ON(args->local_msgqueue_pa == 0);
		DBUG_ON(args->local_nentries == 0);
		DBUG_ON(args->remote_nentries == 0);

		ret = xpc_arch_ops.save_remote_msgqueue_pa(ch,
						      args->local_msgqueue_pa);
		if (ret != xpSuccess) {
			XPC_DISCONNECT_CHANNEL(ch, ret, &irq_flags);
			goto out;
		}
		ch->flags |= XPC_C_ROPENREPLY;

		if (args->local_nentries < ch->remote_nentries) {
			dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY: new "
				"remote_nentries=%d, old remote_nentries=%d, "
				"partid=%d, channel=%d\n",
				args->local_nentries, ch->remote_nentries,
				ch->partid, ch->number);

			ch->remote_nentries = args->local_nentries;
		}
		if (args->remote_nentries < ch->local_nentries) {
			dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY: new "
				"local_nentries=%d, old local_nentries=%d, "
				"partid=%d, channel=%d\n",
				args->remote_nentries, ch->local_nentries,
				ch->partid, ch->number);

			ch->local_nentries = args->remote_nentries;
		}

		xpc_process_connect(ch, &irq_flags);
	}

	if (chctl_flags & XPC_CHCTL_OPENCOMPLETE) {

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENCOMPLETE received from "
			"partid=%d, channel=%d\n", ch->partid, ch->number);

		if (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			goto out;

		if (!(ch->flags & XPC_C_OPENREQUEST) ||
		    !(ch->flags & XPC_C_OPENREPLY)) {
			XPC_DISCONNECT_CHANNEL(ch, xpOpenCloseError,
					       &irq_flags);
			goto out;
		}

		DBUG_ON(!(ch->flags & XPC_C_ROPENREQUEST));
		DBUG_ON(!(ch->flags & XPC_C_ROPENREPLY));
		DBUG_ON(!(ch->flags & XPC_C_CONNECTED));

		ch->flags |= XPC_C_ROPENCOMPLETE;

		xpc_process_connect(ch, &irq_flags);
		create_kthread = 1;
	}

out:
	spin_unlock_irqrestore(&ch->lock, irq_flags);

	if (create_kthread)
		xpc_create_kthreads(ch, 1, 0);
}