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
struct bitmap {TYPE_1__* mddev; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ resync_max_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_end_sync (struct bitmap*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

void bitmap_close_sync(struct bitmap *bitmap)
{
	/* Sync has finished, and any bitmap chunks that weren't synced
	 * properly have been aborted.  It remains to us to clear the
	 * RESYNC bit wherever it is still on
	 */
	sector_t sector = 0;
	sector_t blocks;
	if (!bitmap)
		return;
	while (sector < bitmap->mddev->resync_max_sectors) {
		bitmap_end_sync(bitmap, sector, &blocks, 0);
		sector += blocks;
	}
}