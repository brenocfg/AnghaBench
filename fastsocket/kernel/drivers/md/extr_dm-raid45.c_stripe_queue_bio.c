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
struct stripe {int /*<<< orphan*/  region; } ;
struct TYPE_2__ {int /*<<< orphan*/  rh; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ recover; } ;
struct raid_address {int /*<<< orphan*/  di; } ;
struct bio_list {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_sector; } ;

/* Variables and functions */
 struct bio_list* BL (struct stripe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHUNK (struct stripe*,int /*<<< orphan*/ ) ; 
 int READ ; 
 scalar_t__ S_BIOS_ADDED_READ ; 
 scalar_t__ S_BIOS_ADDED_WRITE ; 
 scalar_t__ S_IOS_POST ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int chunk_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_address (struct raid_set*,int /*<<< orphan*/ ,struct raid_address*) ; 
 struct stripe* stripe_find (struct raid_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_flush_add (struct stripe*) ; 

__attribute__((used)) static int stripe_queue_bio(struct raid_set *rs, struct bio *bio,
			    struct bio_list *reject)
{
	struct raid_address addr;
	struct stripe *stripe;

	stripe = stripe_find(rs, raid_address(rs, bio->bi_sector, &addr));
	if (stripe) {
		int r = 0, rw = bio_data_dir(bio);

		/* Distinguish reads and writes. */
		bio_list_add(BL(stripe, addr.di, rw), bio);

		if (rw == READ)
			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_BIOS_ADDED_READ);
		else {
			/* Inrement pending write count on region. */
			dm_rh_inc(rs->recover.rh, stripe->region);
			r = 1;

			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_BIOS_ADDED_WRITE);
		}

		/*
		 * Put on io (flush) list in case of
		 * initial bio queued to chunk.
		 */
		if (chunk_get(CHUNK(stripe, addr.di)) == 1)
			stripe_flush_add(stripe);

		return r;
	}

	/* Got no stripe from cache or failed to lock it -> reject bio. */
	bio_list_add(reject, bio);
	atomic_inc(rs->stats + S_IOS_POST); /* REMOVEME: statistics. */
	return 0;
}