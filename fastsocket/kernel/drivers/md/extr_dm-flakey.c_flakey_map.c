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
union map_info {int ll; } ;
struct flakey_c {unsigned int start_time; unsigned int up_interval; unsigned int down_interval; scalar_t__ corrupt_bio_rw; scalar_t__ corrupt_bio_byte; int /*<<< orphan*/  flags; } ;
struct dm_target {struct flakey_c* private; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int /*<<< orphan*/  DROP_WRITES ; 
 int EIO ; 
 unsigned int HZ ; 
 scalar_t__ READ ; 
 scalar_t__ WRITE ; 
 scalar_t__ all_corrupt_bio_flags_match (struct bio*,struct flakey_c*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  corrupt_bio_data (struct bio*,struct flakey_c*) ; 
 int /*<<< orphan*/  flakey_map_bio (struct dm_target*,struct bio*) ; 
 unsigned int jiffies ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flakey_map(struct dm_target *ti, struct bio *bio,
		      union map_info *map_context)
{
	struct flakey_c *fc = ti->private;
	unsigned elapsed;

	/* Are we alive ? */
	elapsed = (jiffies - fc->start_time) / HZ;
	if (elapsed % (fc->up_interval + fc->down_interval) >= fc->up_interval) {
		/*
		 * Flag this bio as submitted while down.
		 */
		map_context->ll = 1;

		/*
		 * Map reads as normal.
		 */
		if (bio_data_dir(bio) == READ)
			goto map_bio;

		/*
		 * Drop writes?
		 */
		if (test_bit(DROP_WRITES, &fc->flags)) {
			bio_endio(bio, 0);
			return DM_MAPIO_SUBMITTED;
		}

		/*
		 * Corrupt matching writes.
		 */
		if (fc->corrupt_bio_byte && (fc->corrupt_bio_rw == WRITE)) {
			if (all_corrupt_bio_flags_match(bio, fc))
				corrupt_bio_data(bio, fc);
			goto map_bio;
		}

		/*
		 * By default, error all I/O.
		 */
		return -EIO;
	}

map_bio:
	flakey_map_bio(ti, bio);

	return DM_MAPIO_REMAPPED;
}