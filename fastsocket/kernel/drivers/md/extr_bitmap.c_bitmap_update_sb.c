#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sb_page; } ;
struct bitmap {scalar_t__ events_cleared; int flags; TYPE_3__ storage; TYPE_2__* mddev; } ;
struct TYPE_10__ {void* sectors_reserved; void* chunksize; void* sync_size; void* write_behind; void* daemon_sleep; void* state; void* events_cleared; void* events; } ;
typedef  TYPE_4__ bitmap_super_t ;
struct TYPE_7__ {int daemon_sleep; int max_write_behind; int chunksize; int space; scalar_t__ external; } ;
struct TYPE_8__ {scalar_t__ events; scalar_t__ resync_max_sectors; TYPE_1__ bitmap_info; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  KM_USER0 ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 TYPE_4__* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_page (struct bitmap*,int /*<<< orphan*/ ,int) ; 

void bitmap_update_sb(struct bitmap *bitmap)
{
	bitmap_super_t *sb;

	if (!bitmap || !bitmap->mddev) /* no bitmap for this array */
		return;
	if (bitmap->mddev->bitmap_info.external)
		return;
	if (!bitmap->storage.sb_page) /* no superblock */
		return;
	sb = kmap_atomic(bitmap->storage.sb_page, KM_USER0);
	sb->events = cpu_to_le64(bitmap->mddev->events);
	if (bitmap->mddev->events < bitmap->events_cleared)
		/* rocking back to read-only */
		bitmap->events_cleared = bitmap->mddev->events;
	sb->events_cleared = cpu_to_le64(bitmap->events_cleared);
	sb->state = cpu_to_le32(bitmap->flags);
	/* Just in case these have been changed via sysfs: */
	sb->daemon_sleep = cpu_to_le32(bitmap->mddev->bitmap_info.daemon_sleep/HZ);
	sb->write_behind = cpu_to_le32(bitmap->mddev->bitmap_info.max_write_behind);
	/* This might have been changed by a reshape */
	sb->sync_size = cpu_to_le64(bitmap->mddev->resync_max_sectors);
	sb->chunksize = cpu_to_le32(bitmap->mddev->bitmap_info.chunksize);
	sb->sectors_reserved = cpu_to_le32(bitmap->mddev->
					   bitmap_info.space);
	kunmap_atomic(sb, KM_USER0);
	write_page(bitmap, bitmap->storage.sb_page, 1);
}