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
struct stripe_chunk {int dummy; } ;
struct stripe {int /*<<< orphan*/  region; int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  rh; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ recover; } ;
struct page_list {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct stripe_chunk* CHUNK (struct stripe*,int) ; 
 struct page_list* PL (struct stripe*,int) ; 
 scalar_t__ READ ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ S_BIOS_ENDIO_READ ; 
 scalar_t__ S_BIOS_ENDIO_WRITE ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  bio_copy_page_list (scalar_t__,struct stripe*,struct page_list*,struct bio*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  chunk_put (struct stripe_chunk*) ; 
 int /*<<< orphan*/  dm_rh_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_put (struct raid_set*) ; 
 int /*<<< orphan*/  stripe_put (struct stripe*) ; 

__attribute__((used)) static void bio_list_endio(struct stripe *stripe, struct bio_list *bl,
			   int p, int error)
{
	struct raid_set *rs = RS(stripe->sc);
	struct bio *bio;
	struct page_list *pl = PL(stripe, p);
	struct stripe_chunk *chunk = CHUNK(stripe, p);

	/* Update region counters. */
	while ((bio = bio_list_pop(bl))) {
		if (bio_data_dir(bio) == WRITE)
			/* Drop io pending count for any writes. */
			dm_rh_dec(rs->recover.rh, stripe->region);
		else if (!error)
			/* Copy data accross. */
			bio_copy_page_list(READ, stripe, pl, bio);

		bio_endio(bio, error);

		/* REMOVEME: statistics. */
		atomic_inc(rs->stats + (bio_data_dir(bio) == READ ?
			   S_BIOS_ENDIO_READ : S_BIOS_ENDIO_WRITE));

		chunk_put(chunk);
		stripe_put(stripe);
		io_put(rs);	/* Wake any suspend waiters on last bio. */
	}
}