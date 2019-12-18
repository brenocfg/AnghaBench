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
struct xpc_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_MAX_NCHANNELS ; 
 short xp_max_npartitions ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (struct xpc_partition*) ; 

void
xpc_initiate_connect(int ch_number)
{
	short partid;
	struct xpc_partition *part;
	struct xpc_channel *ch;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	for (partid = 0; partid < xp_max_npartitions; partid++) {
		part = &xpc_partitions[partid];

		if (xpc_part_ref(part)) {
			ch = &part->channels[ch_number];

			/*
			 * Initiate the establishment of a connection on the
			 * newly registered channel to the remote partition.
			 */
			xpc_wakeup_channel_mgr(part);
			xpc_part_deref(part);
		}
	}
}