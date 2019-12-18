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
struct dm_exception_table {int dummy; } ;
struct dm_snapshot {scalar_t__ valid; struct dm_exception_store* store; TYPE_1__* ti; struct dm_exception_table complete; } ;
struct dm_exception_store {int /*<<< orphan*/  chunk_size; struct dm_snapshot* snap; } ;
struct TYPE_2__ {int /*<<< orphan*/  split_io; } ;

/* Variables and functions */

__attribute__((used)) static void __handover_exceptions(struct dm_snapshot *snap_src,
				  struct dm_snapshot *snap_dest)
{
	union {
		struct dm_exception_table table_swap;
		struct dm_exception_store *store_swap;
	} u;

	/*
	 * Swap all snapshot context information between the two instances.
	 */
	u.table_swap = snap_dest->complete;
	snap_dest->complete = snap_src->complete;
	snap_src->complete = u.table_swap;

	u.store_swap = snap_dest->store;
	snap_dest->store = snap_src->store;
	snap_src->store = u.store_swap;

	snap_dest->store->snap = snap_dest;
	snap_src->store->snap = snap_src;

	snap_dest->ti->split_io = snap_dest->store->chunk_size;
	snap_dest->valid = snap_src->valid;

	/*
	 * Set source invalid to ensure it receives no further I/O.
	 */
	snap_src->valid = 0;
}