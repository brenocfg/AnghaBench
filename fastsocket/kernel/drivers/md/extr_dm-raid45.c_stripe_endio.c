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
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {unsigned int raid_devs; } ;
struct raid_set {TYPE_1__ set; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 struct bio_list* BL_CHUNK (struct stripe_chunk*,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct stripe_chunk* CHUNK (struct stripe*,unsigned int) ; 
 scalar_t__ ChunkDirty (struct stripe_chunk*) ; 
 scalar_t__ ChunkError (struct stripe_chunk*) ; 
 int ChunkLocked (struct stripe_chunk*) ; 
 int /*<<< orphan*/  ChunkUptodate (struct stripe_chunk*) ; 
 int /*<<< orphan*/  EIO ; 
 int READ ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 int RSDead (struct raid_set*) ; 
 int /*<<< orphan*/  RSDegraded (struct raid_set*) ; 
 scalar_t__ bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_endio (struct stripe*,struct bio_list*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void stripe_endio(int rw, struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned p = rs->set.raid_devs;
	int write = (rw != READ);

	while (p--) {
		struct stripe_chunk *chunk = CHUNK(stripe, p);
		struct bio_list *bl;

		BUG_ON(ChunkLocked(chunk));

		bl = BL_CHUNK(chunk, rw);
		if (bio_list_empty(bl))
			continue;

		if (unlikely(ChunkError(chunk) || !ChunkUptodate(chunk))) {
			/* RAID set dead. */
			if (unlikely(RSDead(rs)))
				bio_list_endio(stripe, bl, p, -EIO);
			/* RAID set degraded. */
			else if (write)
				bio_list_endio(stripe, bl, p, 0);
		} else {
			BUG_ON(!RSDegraded(rs) && ChunkDirty(chunk));
			bio_list_endio(stripe, bl, p, 0);
		}
	}
}