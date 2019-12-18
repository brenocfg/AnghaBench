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
typedef  int u32 ;
struct xpc_channel {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_allocate_wq; int /*<<< orphan*/  n_on_msg_allocate_wq; int /*<<< orphan*/  idle_wq; int /*<<< orphan*/  kthreads_idle; int /*<<< orphan*/  number; int /*<<< orphan*/  partid; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_chctl_closerequest ) (struct xpc_channel*,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_CLOSEREQUEST ; 
 int XPC_C_CONNECTED ; 
 int XPC_C_CONNECTEDCALLOUT_MADE ; 
 int XPC_C_CONNECTING ; 
 int XPC_C_DISCONNECTED ; 
 int XPC_C_DISCONNECTING ; 
 int XPC_C_DISCONNECTINGCALLOUT ; 
 int XPC_C_OPENREPLY ; 
 int XPC_C_OPENREQUEST ; 
 int XPC_C_ROPENREPLY ; 
 int XPC_C_ROPENREQUEST ; 
 int XPC_C_WASCONNECTED ; 
 int /*<<< orphan*/  XPC_SET_REASON (struct xpc_channel*,int,int const) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xpc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/  xpc_create_kthreads (struct xpc_channel*,int,int) ; 

void
xpc_disconnect_channel(const int line, struct xpc_channel *ch,
		       enum xp_retval reason, unsigned long *irq_flags)
{
	u32 channel_was_connected = (ch->flags & XPC_C_CONNECTED);

	DBUG_ON(!spin_is_locked(&ch->lock));

	if (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
		return;

	DBUG_ON(!(ch->flags & (XPC_C_CONNECTING | XPC_C_CONNECTED)));

	dev_dbg(xpc_chan, "reason=%d, line=%d, partid=%d, channel=%d\n",
		reason, line, ch->partid, ch->number);

	XPC_SET_REASON(ch, reason, line);

	ch->flags |= (XPC_C_CLOSEREQUEST | XPC_C_DISCONNECTING);
	/* some of these may not have been set */
	ch->flags &= ~(XPC_C_OPENREQUEST | XPC_C_OPENREPLY |
		       XPC_C_ROPENREQUEST | XPC_C_ROPENREPLY |
		       XPC_C_CONNECTING | XPC_C_CONNECTED);

	xpc_arch_ops.send_chctl_closerequest(ch, irq_flags);

	if (channel_was_connected)
		ch->flags |= XPC_C_WASCONNECTED;

	spin_unlock_irqrestore(&ch->lock, *irq_flags);

	/* wake all idle kthreads so they can exit */
	if (atomic_read(&ch->kthreads_idle) > 0) {
		wake_up_all(&ch->idle_wq);

	} else if ((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
		   !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) {
		/* start a kthread that will do the xpDisconnecting callout */
		xpc_create_kthreads(ch, 1, 1);
	}

	/* wake those waiting to allocate an entry from the local msg queue */
	if (atomic_read(&ch->n_on_msg_allocate_wq) > 0)
		wake_up(&ch->msg_allocate_wq);

	spin_lock_irqsave(&ch->lock, *irq_flags);
}