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
union map_info {unsigned int ll; } ;
struct flakey_c {scalar_t__ corrupt_bio_rw; scalar_t__ corrupt_bio_byte; } ;
struct dm_target {struct flakey_c* private; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 scalar_t__ all_corrupt_bio_flags_match (struct bio*,struct flakey_c*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  corrupt_bio_data (struct bio*,struct flakey_c*) ; 

__attribute__((used)) static int flakey_end_io(struct dm_target *ti, struct bio *bio,
			 int error, union map_info *map_context)
{
	struct flakey_c *fc = ti->private;
	unsigned bio_submitted_while_down = map_context->ll;

	/*
	 * Corrupt successful READs while in down state.
	 * If flags were specified, only corrupt those that match.
	 */
	if (fc->corrupt_bio_byte && !error && bio_submitted_while_down &&
	    (bio_data_dir(bio) == READ) && (fc->corrupt_bio_rw == READ) &&
	    all_corrupt_bio_flags_match(bio, fc))
		corrupt_bio_data(bio, fc);

	return error;
}