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
struct dm_snapshot {int /*<<< orphan*/  kcopyd_client; } ;
struct dm_snap_pending_exception {void* full_bio_private; int /*<<< orphan*/  full_bio_end_io; struct bio* full_bio; struct dm_snapshot* snap; } ;
struct bio {void* bi_private; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_callback ; 
 void* dm_kcopyd_prepare_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  full_bio_end_io ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static void start_full_bio(struct dm_snap_pending_exception *pe,
			   struct bio *bio)
{
	struct dm_snapshot *s = pe->snap;
	void *callback_data;

	pe->full_bio = bio;
	pe->full_bio_end_io = bio->bi_end_io;
	pe->full_bio_private = bio->bi_private;

	callback_data = dm_kcopyd_prepare_callback(s->kcopyd_client,
						   copy_callback, pe);

	bio->bi_end_io = full_bio_end_io;
	bio->bi_private = callback_data;

	generic_make_request(bio);
}