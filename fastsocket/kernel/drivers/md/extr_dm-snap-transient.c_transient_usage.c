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
struct transient_c {scalar_t__ next_free; } ;
struct dm_exception_store {int /*<<< orphan*/  snap; scalar_t__ context; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 TYPE_1__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 scalar_t__ get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transient_usage(struct dm_exception_store *store,
			    sector_t *total_sectors,
			    sector_t *sectors_allocated,
			    sector_t *metadata_sectors)
{
	*sectors_allocated = ((struct transient_c *) store->context)->next_free;
	*total_sectors = get_dev_size(dm_snap_cow(store->snap)->bdev);
	*metadata_sectors = 0;
}