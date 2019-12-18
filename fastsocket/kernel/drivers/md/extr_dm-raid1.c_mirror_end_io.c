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
union map_info {struct dm_raid1_read_record* ptr; int /*<<< orphan*/  ll; } ;
struct mirror_set {int /*<<< orphan*/  read_record_pool; int /*<<< orphan*/  rh; } ;
struct mirror {TYPE_1__* dev; } ;
struct dm_target {scalar_t__ private; } ;
struct dm_bio_details {int dummy; } ;
struct dm_raid1_read_record {struct dm_bio_details details; struct mirror* m; } ;
struct bio {int bi_rw; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_FLUSH ; 
 int /*<<< orphan*/  BIO_RW_AHEAD ; 
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
 int /*<<< orphan*/  DM_RAID1_READ_ERROR ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int WRITE ; 
 int bio_rw (struct bio*) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ default_ok (struct mirror*) ; 
 int /*<<< orphan*/  dm_bio_restore (struct dm_bio_details*,struct bio*) ; 
 int /*<<< orphan*/  dm_rh_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_mirror (struct mirror*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct dm_raid1_read_record*,int /*<<< orphan*/ ) ; 
 scalar_t__ mirror_available (struct mirror_set*,struct bio*) ; 
 int /*<<< orphan*/  queue_bio (struct mirror_set*,struct bio*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mirror_end_io(struct dm_target *ti, struct bio *bio,
			 int error, union map_info *map_context)
{
	int rw = bio_rw(bio);
	struct mirror_set *ms = (struct mirror_set *) ti->private;
	struct mirror *m = NULL;
	struct dm_bio_details *bd = NULL;
	struct dm_raid1_read_record *read_record = map_context->ptr;

	/*
	 * We need to dec pending if this was a write.
	 */
	if (rw == WRITE) {
		if (!(bio->bi_rw & (BIO_FLUSH | BIO_DISCARD)))
			dm_rh_dec(ms->rh, map_context->ll);
		return error;
	}

	if (error == -EOPNOTSUPP)
		goto out;

	if ((error == -EWOULDBLOCK) && bio_rw_flagged(bio, BIO_RW_AHEAD))
		goto out;

	if (unlikely(error)) {
		if (!read_record) {
			/*
			 * There wasn't enough memory to record necessary
			 * information for a retry or there was no other
			 * mirror in-sync.
			 */
			DMERR_LIMIT("Mirror read failed.");
			return -EIO;
		}

		m = read_record->m;

		DMERR("Mirror read failed from %s. Trying alternative device.",
		      m->dev->name);

		fail_mirror(m, DM_RAID1_READ_ERROR);

		/*
		 * A failed read is requeued for another attempt using an intact
		 * mirror.
		 */
		if (default_ok(m) || mirror_available(ms, bio)) {
			bd = &read_record->details;

			dm_bio_restore(bd, bio);
			mempool_free(read_record, ms->read_record_pool);
			map_context->ptr = NULL;
			queue_bio(ms, bio, rw);
			return 1;
		}
		DMERR("All replicated volumes dead, failing I/O");
	}

out:
	if (read_record) {
		mempool_free(read_record, ms->read_record_pool);
		map_context->ptr = NULL;
	}

	return error;
}