#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union map_info {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  target_request_nr; } ;
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {scalar_t__ first_merging_chunk; scalar_t__ num_merging_chunks; int /*<<< orphan*/  lock; TYPE_2__* origin; int /*<<< orphan*/  bios_queued_during_merge; int /*<<< orphan*/  complete; int /*<<< orphan*/  valid; int /*<<< orphan*/  store; TYPE_1__* cow; } ;
struct dm_exception {int dummy; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
typedef  scalar_t__ chunk_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_rw (struct bio*) ; 
 struct dm_exception* dm_lookup_exception (int /*<<< orphan*/ *,scalar_t__) ; 
 int do_origin (TYPE_2__*,struct bio*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_exception (struct dm_snapshot*,struct dm_exception*,struct bio*,scalar_t__) ; 
 scalar_t__ sector_to_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * track_chunk (struct dm_snapshot*,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snapshot_merge_map(struct dm_target *ti, struct bio *bio,
			      union map_info *map_context)
{
	struct dm_exception *e;
	struct dm_snapshot *s = ti->private;
	int r = DM_MAPIO_REMAPPED;
	chunk_t chunk;

	if (bio->bi_rw & BIO_FLUSH) {
		if (!map_context->target_request_nr)
			bio->bi_bdev = s->origin->bdev;
		else
			bio->bi_bdev = s->cow->bdev;
		map_context->ptr = NULL;
		return DM_MAPIO_REMAPPED;
	}

	chunk = sector_to_chunk(s->store, bio->bi_sector);

	down_write(&s->lock);

	/* Full merging snapshots are redirected to the origin */
	if (!s->valid)
		goto redirect_to_origin;

	/* If the block is already remapped - use that */
	e = dm_lookup_exception(&s->complete, chunk);
	if (e) {
		/* Queue writes overlapping with chunks being merged */
		if (bio_rw(bio) == WRITE &&
		    chunk >= s->first_merging_chunk &&
		    chunk < (s->first_merging_chunk +
			     s->num_merging_chunks)) {
			bio->bi_bdev = s->origin->bdev;
			bio_list_add(&s->bios_queued_during_merge, bio);
			r = DM_MAPIO_SUBMITTED;
			goto out_unlock;
		}

		remap_exception(s, e, bio, chunk);

		if (bio_rw(bio) == WRITE)
			map_context->ptr = track_chunk(s, chunk);
		goto out_unlock;
	}

redirect_to_origin:
	bio->bi_bdev = s->origin->bdev;

	if (bio_rw(bio) == WRITE) {
		up_write(&s->lock);
		return do_origin(s->origin, bio);
	}

out_unlock:
	up_write(&s->lock);

	return r;
}