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
struct TYPE_4__ {scalar_t__ lists; } ;
struct TYPE_3__ {struct dm_rh_client* rh; } ;
struct raid_set {scalar_t__ stats; TYPE_2__ sc; TYPE_1__ recover; } ;
struct dm_rh_client {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
 int /*<<< orphan*/  DM_RH_RECOVERING ; 
 scalar_t__ LIST_FLUSH ; 
 scalar_t__ RSProhibitWrites (struct raid_set*) ; 
 scalar_t__ S_BARRIER ; 
 scalar_t__ S_DELAYED_BIOS ; 
 scalar_t__ S_SUM_DELAYED_BIOS ; 
 int /*<<< orphan*/  SetRSBandwidth (struct raid_set*) ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  _sector (struct raid_set*,struct bio*) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int bio_empty_barrier (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge_head (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_push (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  dm_rh_delay_by_region (struct dm_rh_client*,struct bio*,int /*<<< orphan*/ ) ; 
 int dm_rh_flush (struct dm_rh_client*) ; 
 int /*<<< orphan*/  dm_rh_sector_to_region (struct dm_rh_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (scalar_t__) ; 
 int region_state (struct raid_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_active (TYPE_2__*) ; 
 scalar_t__ stripe_queue_bio (struct raid_set*,struct bio*,struct bio_list*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_ios(struct raid_set *rs, struct bio_list *ios)
{
	int r;
	unsigned flush = 0, delay = 0;
	sector_t sector;
	struct dm_rh_client *rh = rs->recover.rh;
	struct bio *bio;
	struct bio_list reject;

	bio_list_init(&reject);

	/*
	 * Classify each io:
	 *    o delay writes to recovering regions (let reads go through)
	 *    o queue io to all other regions
	 */
	while ((bio = bio_list_pop(ios))) {
		/*
		 * In case we get a barrier bio, push it back onto
		 * the input queue unless all work queues are empty
		 * and the stripe cache is inactive.
		 */
		if (unlikely(bio_empty_barrier(bio))) {
			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_BARRIER);
			if (delay ||
			    !list_empty(rs->sc.lists + LIST_FLUSH) ||
			    !bio_list_empty(&reject) ||
			    sc_active(&rs->sc)) {
				bio_list_push(ios, bio);
				break;
			}
		}

		/* If writes prohibited because of failures -> postpone. */
		if (RSProhibitWrites(rs) && bio_data_dir(bio) == WRITE) {
			bio_list_add(&reject, bio);
			continue;
		}

		/* Check for recovering regions. */
		sector = _sector(rs, bio);
		r = region_state(rs, sector, DM_RH_RECOVERING);
		if (unlikely(r)) {
			delay++;
			/* Wait writing to recovering regions. */
			dm_rh_delay_by_region(rh, bio,
					      dm_rh_sector_to_region(rh,
								     sector));
			/* REMOVEME: statistics.*/
			atomic_inc(rs->stats + S_DELAYED_BIOS);
			atomic_inc(rs->stats + S_SUM_DELAYED_BIOS);

			/* Force bandwidth tests in recovery. */
			SetRSBandwidth(rs);
		} else {
			/*
			 * Process ios to non-recovering regions by queueing
			 * them to stripes (does dm_rh_inc()) for writes).
			 */
			flush += stripe_queue_bio(rs, bio, &reject);
		}
	}

	if (flush) {
		/* FIXME: better error handling. */
		r = dm_rh_flush(rh); /* Writes got queued -> flush dirty log. */
		if (r)
			DMERR_LIMIT("dirty log flush");
	}

	/* Merge any rejected bios back to the head of the input list. */
	bio_list_merge_head(ios, &reject);
}