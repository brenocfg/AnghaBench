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
struct xpc_channel_sn2 {int /*<<< orphan*/ * notify_queue; int /*<<< orphan*/ * local_msgqueue; int /*<<< orphan*/ * local_msgqueue_base; } ;
struct TYPE_2__ {struct xpc_channel_sn2 sn2; } ;
struct xpc_channel {int flags; TYPE_1__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_C_SETUP ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int xpSuccess ; 
 int xpc_allocate_local_msgqueue_sn2 (struct xpc_channel*) ; 
 int xpc_allocate_remote_msgqueue_sn2 (struct xpc_channel*) ; 

__attribute__((used)) static enum xp_retval
xpc_setup_msg_structures_sn2(struct xpc_channel *ch)
{
	struct xpc_channel_sn2 *ch_sn2 = &ch->sn.sn2;
	enum xp_retval ret;

	DBUG_ON(ch->flags & XPC_C_SETUP);

	ret = xpc_allocate_local_msgqueue_sn2(ch);
	if (ret == xpSuccess) {

		ret = xpc_allocate_remote_msgqueue_sn2(ch);
		if (ret != xpSuccess) {
			kfree(ch_sn2->local_msgqueue_base);
			ch_sn2->local_msgqueue = NULL;
			kfree(ch_sn2->notify_queue);
			ch_sn2->notify_queue = NULL;
		}
	}
	return ret;
}