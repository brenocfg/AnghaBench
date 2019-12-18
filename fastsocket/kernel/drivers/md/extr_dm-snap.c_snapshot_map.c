#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union map_info {int /*<<< orphan*/  ptr; } ;
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int /*<<< orphan*/  lock; TYPE_2__* origin; TYPE_3__* store; int /*<<< orphan*/  complete; int /*<<< orphan*/  valid; TYPE_1__* cow; } ;
struct dm_exception {int dummy; } ;
struct dm_snap_pending_exception {int started; int /*<<< orphan*/  snapshot_bios; struct dm_exception e; } ;
struct bio {int bi_rw; int bi_size; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
typedef  int /*<<< orphan*/  chunk_t ;
struct TYPE_6__ {int chunk_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SECTOR_SHIFT ; 
 scalar_t__ WRITE ; 
 struct dm_snap_pending_exception* __find_pending_exception (struct dm_snapshot*,struct dm_snap_pending_exception*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __invalidate_snapshot (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 struct dm_snap_pending_exception* __lookup_pending_exception (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 struct dm_snap_pending_exception* alloc_pending_exception (struct dm_snapshot*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_rw (struct bio*) ; 
 struct dm_exception* dm_lookup_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pending_exception (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  remap_exception (struct dm_snapshot*,struct dm_exception*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_to_chunk (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_copy (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  start_full_bio (struct dm_snap_pending_exception*,struct bio*) ; 
 int /*<<< orphan*/  track_chunk (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snapshot_map(struct dm_target *ti, struct bio *bio,
			union map_info *map_context)
{
	struct dm_exception *e;
	struct dm_snapshot *s = ti->private;
	int r = DM_MAPIO_REMAPPED;
	chunk_t chunk;
	struct dm_snap_pending_exception *pe = NULL;

	if (bio->bi_rw & BIO_FLUSH) {
		bio->bi_bdev = s->cow->bdev;
		return DM_MAPIO_REMAPPED;
	}

	chunk = sector_to_chunk(s->store, bio->bi_sector);

	/* Full snapshots are not usable */
	/* To get here the table must be live so s->active is always set. */
	if (!s->valid)
		return -EIO;

	/* FIXME: should only take write lock if we need
	 * to copy an exception */
	down_write(&s->lock);

	if (!s->valid) {
		r = -EIO;
		goto out_unlock;
	}

	/* If the block is already remapped - use that, else remap it */
	e = dm_lookup_exception(&s->complete, chunk);
	if (e) {
		remap_exception(s, e, bio, chunk);
		goto out_unlock;
	}

	/*
	 * Write to snapshot - higher level takes care of RW/RO
	 * flags so we should only get this if we are
	 * writeable.
	 */
	if (bio_rw(bio) == WRITE) {
		pe = __lookup_pending_exception(s, chunk);
		if (!pe) {
			up_write(&s->lock);
			pe = alloc_pending_exception(s);
			down_write(&s->lock);

			if (!s->valid) {
				free_pending_exception(pe);
				r = -EIO;
				goto out_unlock;
			}

			e = dm_lookup_exception(&s->complete, chunk);
			if (e) {
				free_pending_exception(pe);
				remap_exception(s, e, bio, chunk);
				goto out_unlock;
			}

			pe = __find_pending_exception(s, pe, chunk);
			if (!pe) {
				__invalidate_snapshot(s, -ENOMEM);
				r = -EIO;
				goto out_unlock;
			}
		}

		remap_exception(s, &pe->e, bio, chunk);

		r = DM_MAPIO_SUBMITTED;

		if (!pe->started &&
		    bio->bi_size == (s->store->chunk_size << SECTOR_SHIFT)) {
			pe->started = 1;
			up_write(&s->lock);
			start_full_bio(pe, bio);
			goto out;
		}

		bio_list_add(&pe->snapshot_bios, bio);

		if (!pe->started) {
			/* this is protected by snap->lock */
			pe->started = 1;
			up_write(&s->lock);
			start_copy(pe);
			goto out;
		}
	} else {
		bio->bi_bdev = s->origin->bdev;
		map_context->ptr = track_chunk(s, chunk);
	}

out_unlock:
	up_write(&s->lock);
out:
	return r;
}