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
struct xpc_partition {int nchannels; TYPE_2__* channels; } ;
struct xpc_channel_uv {int /*<<< orphan*/  recv_msg_list; int /*<<< orphan*/  msg_slot_free_list; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_3__ {struct xpc_channel_uv uv; } ;
struct TYPE_4__ {TYPE_1__ sn; } ;

/* Variables and functions */
 int xpSuccess ; 
 int /*<<< orphan*/  xpc_init_fifo_uv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum xp_retval
xpc_setup_ch_structures_uv(struct xpc_partition *part)
{
	struct xpc_channel_uv *ch_uv;
	int ch_number;

	for (ch_number = 0; ch_number < part->nchannels; ch_number++) {
		ch_uv = &part->channels[ch_number].sn.uv;

		xpc_init_fifo_uv(&ch_uv->msg_slot_free_list);
		xpc_init_fifo_uv(&ch_uv->recv_msg_list);
	}

	return xpSuccess;
}