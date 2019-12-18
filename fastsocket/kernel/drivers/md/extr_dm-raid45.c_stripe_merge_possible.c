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
struct stripe_chunk {int dummy; } ;
struct TYPE_4__ {unsigned int parity; } ;
struct stripe {TYPE_2__ idx; int /*<<< orphan*/  sc; } ;
struct TYPE_3__ {unsigned int raid_devs; unsigned int data_devs; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ set; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CHUNK (struct stripe_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct stripe_chunk* CHUNK (struct stripe*,unsigned int) ; 
 int /*<<< orphan*/  ClearChunkIo (struct stripe_chunk*) ; 
 scalar_t__ DevFailed (scalar_t__) ; 
 int EPERM ; 
 int /*<<< orphan*/  READ ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ RSCheckOverwrite (struct raid_set*) ; 
 scalar_t__ S_CANT_MERGE ; 
 scalar_t__ S_CAN_MERGE ; 
 scalar_t__ S_OVERWRITE ; 
 scalar_t__ S_PROHIBITCHUNKIO ; 
 int /*<<< orphan*/  SetChunkIo (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetStripeReconstruct (struct stripe*) ; 
 int /*<<< orphan*/  StripeReconstruct (struct stripe*) ; 
 int /*<<< orphan*/  WRITE_MERGED ; 
 int /*<<< orphan*/  WRITE_QUEUED ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parity_xor (struct stripe*) ; 
 scalar_t__ stripe_check_chunk_overwrite (struct stripe*,unsigned int) ; 
 struct stripe_chunk* stripe_chunk_check (struct stripe*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  stripe_zero_chunk (struct stripe*,unsigned int) ; 

__attribute__((used)) static int stripe_merge_possible(struct stripe *stripe, int nosync)
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned chunks_overwrite = 0, chunks_prohibited = 0,
		 chunks_uptodate = 0, p = rs->set.raid_devs;

	/* Walk all chunks. */
	while (p--) {
		struct stripe_chunk *chunk;

		/* Prohibit io on broken devices. */
		if (DevFailed(rs->dev + p)) {
			chunk = CHUNK(stripe, p);
			goto prohibit_io;
		}

		/* We can't optimize any further if no chunk. */
		chunk = stripe_chunk_check(stripe, p, &chunks_uptodate);
		if (!chunk || nosync)
			continue;

		/*
		 * We have a chunk, which is not uptodate.
		 *
		 * If this is not parity and we don't have
		 * reads queued, we can optimize further.
		 */
		if (p != stripe->idx.parity &&
		    bio_list_empty(BL_CHUNK(chunk, READ)) &&
		    bio_list_empty(BL_CHUNK(chunk, WRITE_MERGED))) {
			if (bio_list_empty(BL_CHUNK(chunk, WRITE_QUEUED)))
				goto prohibit_io;
			else if (RSCheckOverwrite(rs) &&
				 stripe_check_chunk_overwrite(stripe, p))
				/* Completely overwritten chunk. */
				chunks_overwrite++;
		}

		/* Allow io for chunks with bios and overwritten ones. */
		SetChunkIo(chunk);
		continue;

prohibit_io:
		/* No io for broken devices or for chunks w/o bios. */
		ClearChunkIo(chunk);
		chunks_prohibited++;
		/* REMOVEME: statistics. */
		atomic_inc(RS(stripe->sc)->stats + S_PROHIBITCHUNKIO);
	}

	/* All data chunks will get written over. */
	if (chunks_overwrite == rs->set.data_devs)
		atomic_inc(rs->stats + S_OVERWRITE); /* REMOVEME: statistics.*/
	else if (chunks_uptodate + chunks_prohibited < rs->set.raid_devs) {
		/* We don't have enough chunks to merge. */
		atomic_inc(rs->stats + S_CANT_MERGE); /* REMOVEME: statistics.*/
		return -EPERM;
	}

	/*
	 * If we have all chunks up to date or overwrite them, we
	 * just zero the parity chunk and let stripe_rw() recreate it.
	 */
	if (chunks_uptodate == rs->set.raid_devs ||
	    chunks_overwrite == rs->set.data_devs) {
		stripe_zero_chunk(stripe, stripe->idx.parity);
		BUG_ON(StripeReconstruct(stripe));
		SetStripeReconstruct(stripe);	/* Enforce xor in caller. */
	} else {
		/*
		 * With less chunks, we xor parity out.
		 *
		 * (*4*) We rely on !StripeReconstruct() in chunk_must_xor(),
		 *	 so that only chunks with queued or merged writes
		 *	 are being xored.
		 */
		parity_xor(stripe);
	}

	/*
	 * We do have enough chunks to merge.
	 * All chunks are uptodate or get written over.
	 */
	atomic_inc(rs->stats + S_CAN_MERGE); /* REMOVEME: statistics. */
	return 0;
}