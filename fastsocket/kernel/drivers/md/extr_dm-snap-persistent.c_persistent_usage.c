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
struct pstore {int next_free; int current_area; } ;
struct dm_exception_store {int chunk_size; int /*<<< orphan*/  snap; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int NUM_SNAPSHOT_HDR_CHUNKS ; 
 TYPE_1__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 int get_dev_size (int /*<<< orphan*/ ) ; 
 struct pstore* get_info (struct dm_exception_store*) ; 

__attribute__((used)) static void persistent_usage(struct dm_exception_store *store,
			     sector_t *total_sectors,
			     sector_t *sectors_allocated,
			     sector_t *metadata_sectors)
{
	struct pstore *ps = get_info(store);

	*sectors_allocated = ps->next_free * store->chunk_size;
	*total_sectors = get_dev_size(dm_snap_cow(store->snap)->bdev);

	/*
	 * First chunk is the fixed header.
	 * Then there are (ps->current_area + 1) metadata chunks, each one
	 * separated from the next by ps->exceptions_per_area data chunks.
	 */
	*metadata_sectors = (ps->current_area + 1 + NUM_SNAPSHOT_HDR_CHUNKS) *
			    store->chunk_size;
}