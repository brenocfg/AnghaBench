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
typedef  scalar_t__ u64 ;
struct xpc_channel {int /*<<< orphan*/  number; int /*<<< orphan*/  partid; int /*<<< orphan*/  key; scalar_t__ local_nentries; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpConnected ; 
 int /*<<< orphan*/  xpc_chan ; 

void
xpc_connected_callout(struct xpc_channel *ch)
{
	/* let the registerer know that a connection has been established */

	if (ch->func != NULL) {
		dev_dbg(xpc_chan, "ch->func() called, reason=xpConnected, "
			"partid=%d, channel=%d\n", ch->partid, ch->number);

		ch->func(xpConnected, ch->partid, ch->number,
			 (void *)(u64)ch->local_nentries, ch->key);

		dev_dbg(xpc_chan, "ch->func() returned, reason=xpConnected, "
			"partid=%d, channel=%d\n", ch->partid, ch->number);
	}
}