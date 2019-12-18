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
typedef  union map_info {int dummy; } map_info ;
struct TYPE_2__ {int /*<<< orphan*/  in_lock; int /*<<< orphan*/  in; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ io; } ;
struct dm_target {scalar_t__ begin; struct raid_set* private; } ;
struct bio {int /*<<< orphan*/  bi_sector; } ;

/* Variables and functions */
 int DM_MAPIO_SUBMITTED ; 
 int EIO ; 
 scalar_t__ READ ; 
 scalar_t__ READA ; 
 scalar_t__ S_BIOS_READ ; 
 scalar_t__ S_BIOS_WRITE ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_rw (struct bio*) ; 
 int /*<<< orphan*/  io_get (struct raid_set*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_do_raid (struct raid_set*) ; 

__attribute__((used)) static int raid_map(struct dm_target *ti, struct bio *bio,
		    union map_info *map_context)
{
	/* I don't want to waste stripe cache capacity. */
	if (bio_rw(bio) == READA)
		return -EIO;
	else {
		struct raid_set *rs = ti->private;

		/*
		 * Get io reference to be waiting for to drop
		 * to zero on device suspension/destruction.
		 */
		io_get(rs);
		bio->bi_sector -= ti->begin;	/* Remap sector. */

		/* Queue io to RAID set. */
		mutex_lock(&rs->io.in_lock);
		bio_list_add(&rs->io.in, bio);
		mutex_unlock(&rs->io.in_lock);

		/* Wake daemon to process input list. */
		wake_do_raid(rs);

		/* REMOVEME: statistics. */
		atomic_inc(rs->stats + (bio_data_dir(bio) == READ ?
				        S_BIOS_READ : S_BIOS_WRITE));
		return DM_MAPIO_SUBMITTED;	/* Handle later. */
	}
}