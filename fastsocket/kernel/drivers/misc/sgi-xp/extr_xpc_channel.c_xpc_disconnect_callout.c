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
struct xpc_channel {int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  key; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_chan ; 

void
xpc_disconnect_callout(struct xpc_channel *ch, enum xp_retval reason)
{
	/*
	 * Let the channel's registerer know that the channel is being
	 * disconnected. We don't want to do this if the registerer was never
	 * informed of a connection being made.
	 */

	if (ch->func != NULL) {
		dev_dbg(xpc_chan, "ch->func() called, reason=%d, partid=%d, "
			"channel=%d\n", reason, ch->partid, ch->number);

		ch->func(reason, ch->partid, ch->number, NULL, ch->key);

		dev_dbg(xpc_chan, "ch->func() returned, reason=%d, partid=%d, "
			"channel=%d\n", reason, ch->partid, ch->number);
	}
}