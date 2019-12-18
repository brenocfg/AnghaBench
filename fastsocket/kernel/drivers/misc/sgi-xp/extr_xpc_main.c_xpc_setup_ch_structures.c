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
struct TYPE_3__ {scalar_t__ all_flags; } ;
struct xpc_partition {int nchannels; struct xpc_channel* channels; int /*<<< orphan*/ * remote_openclose_args; struct xpc_channel* remote_openclose_args_base; int /*<<< orphan*/  setup_state; int /*<<< orphan*/  nchannels_engaged; int /*<<< orphan*/  nchannels_active; int /*<<< orphan*/  channel_mgr_wq; int /*<<< orphan*/  channel_mgr_requests; int /*<<< orphan*/  chctl_lock; TYPE_1__ chctl; } ;
struct xpc_channel {short partid; int number; int /*<<< orphan*/  idle_wq; int /*<<< orphan*/  msg_allocate_wq; int /*<<< orphan*/  n_on_msg_allocate_wq; int /*<<< orphan*/  wdisconnect_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  n_to_notify; int /*<<< orphan*/  references; int /*<<< orphan*/  kthreads_active; int /*<<< orphan*/  kthreads_idle; int /*<<< orphan*/  kthreads_assigned; int /*<<< orphan*/  flags; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_4__ {int (* setup_ch_structures ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XPC_C_DISCONNECTED ; 
 int XPC_MAX_NCHANNELS ; 
 int /*<<< orphan*/  XPC_OPENCLOSE_ARGS_SIZE ; 
 short XPC_PARTID (struct xpc_partition*) ; 
 int /*<<< orphan*/  XPC_P_SS_SETUP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xpc_channel*) ; 
 struct xpc_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct xpc_partition*) ; 
 int xpNoMemory ; 
 int xpSuccess ; 
 TYPE_2__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_chan ; 
 int /*<<< orphan*/ * xpc_kzalloc_cacheline_aligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xpc_channel**) ; 

__attribute__((used)) static enum xp_retval
xpc_setup_ch_structures(struct xpc_partition *part)
{
	enum xp_retval ret;
	int ch_number;
	struct xpc_channel *ch;
	short partid = XPC_PARTID(part);

	/*
	 * Allocate all of the channel structures as a contiguous chunk of
	 * memory.
	 */
	DBUG_ON(part->channels != NULL);
	part->channels = kzalloc(sizeof(struct xpc_channel) * XPC_MAX_NCHANNELS,
				 GFP_KERNEL);
	if (part->channels == NULL) {
		dev_err(xpc_chan, "can't get memory for channels\n");
		return xpNoMemory;
	}

	/* allocate the remote open and close args */

	part->remote_openclose_args =
	    xpc_kzalloc_cacheline_aligned(XPC_OPENCLOSE_ARGS_SIZE,
					  GFP_KERNEL, &part->
					  remote_openclose_args_base);
	if (part->remote_openclose_args == NULL) {
		dev_err(xpc_chan, "can't get memory for remote connect args\n");
		ret = xpNoMemory;
		goto out_1;
	}

	part->chctl.all_flags = 0;
	spin_lock_init(&part->chctl_lock);

	atomic_set(&part->channel_mgr_requests, 1);
	init_waitqueue_head(&part->channel_mgr_wq);

	part->nchannels = XPC_MAX_NCHANNELS;

	atomic_set(&part->nchannels_active, 0);
	atomic_set(&part->nchannels_engaged, 0);

	for (ch_number = 0; ch_number < part->nchannels; ch_number++) {
		ch = &part->channels[ch_number];

		ch->partid = partid;
		ch->number = ch_number;
		ch->flags = XPC_C_DISCONNECTED;

		atomic_set(&ch->kthreads_assigned, 0);
		atomic_set(&ch->kthreads_idle, 0);
		atomic_set(&ch->kthreads_active, 0);

		atomic_set(&ch->references, 0);
		atomic_set(&ch->n_to_notify, 0);

		spin_lock_init(&ch->lock);
		init_completion(&ch->wdisconnect_wait);

		atomic_set(&ch->n_on_msg_allocate_wq, 0);
		init_waitqueue_head(&ch->msg_allocate_wq);
		init_waitqueue_head(&ch->idle_wq);
	}

	ret = xpc_arch_ops.setup_ch_structures(part);
	if (ret != xpSuccess)
		goto out_2;

	/*
	 * With the setting of the partition setup_state to XPC_P_SS_SETUP,
	 * we're declaring that this partition is ready to go.
	 */
	part->setup_state = XPC_P_SS_SETUP;

	return xpSuccess;

	/* setup of ch structures failed */
out_2:
	kfree(part->remote_openclose_args_base);
	part->remote_openclose_args = NULL;
out_1:
	kfree(part->channels);
	part->channels = NULL;
	return ret;
}