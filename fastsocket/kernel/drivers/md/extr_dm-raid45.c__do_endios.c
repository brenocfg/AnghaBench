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
struct TYPE_2__ {int recover; } ;
struct stripe {scalar_t__ lists; TYPE_1__ idx; } ;
struct raid_set {scalar_t__ stats; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearStripeMerged (struct stripe*) ; 
 int /*<<< orphan*/  ClearStripeReconstruct (struct stripe*) ; 
 int /*<<< orphan*/  ClearStripeReconstructed (struct stripe*) ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 scalar_t__ LIST_FLUSH ; 
 scalar_t__ LIST_LRU ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ RSDead (struct raid_set*) ; 
 int /*<<< orphan*/  RSProhibitWrites (struct raid_set*) ; 
 scalar_t__ S_REQUEUE ; 
 int /*<<< orphan*/  SetStripeReconstructed (struct stripe*) ; 
 scalar_t__ StripeMerged (struct stripe*) ; 
 scalar_t__ StripeReconstruct (struct stripe*) ; 
 scalar_t__ TestClearStripeError (struct stripe*) ; 
 int /*<<< orphan*/  TestSetRSDeadEndioMessage (struct raid_set*) ; 
 int /*<<< orphan*/  WRITE_MERGED ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (scalar_t__,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (scalar_t__) ; 
 int /*<<< orphan*/  rs_check_degrade (struct stripe*) ; 
 int /*<<< orphan*/  stripe_chunks_unlock (struct stripe*) ; 
 int /*<<< orphan*/  stripe_endio (int /*<<< orphan*/ ,struct stripe*) ; 
 int /*<<< orphan*/  stripe_fail_io (struct stripe*) ; 
 int /*<<< orphan*/  stripe_lru_add (struct stripe*) ; 
 int /*<<< orphan*/  stripe_reconstruct (struct stripe*) ; 
 scalar_t__ stripe_ref (struct stripe*) ; 

__attribute__((used)) static void _do_endios(struct raid_set *rs, struct stripe *stripe,
		       struct list_head *flush_list)
{
	/* First unlock all required chunks. */
	stripe_chunks_unlock(stripe);

	/*
	 * If an io error on a stripe occured, degrade the RAID set
	 * and try to endio as many bios as possible. If any bios can't
	 * be endio processed, requeue the stripe (stripe_ref() != 0).
	 */
	if (TestClearStripeError(stripe)) {
		/*
		 * FIXME: if read, rewrite the failed chunk after reconstruction
		 *        in order to trigger disk bad sector relocation.
		 */
		rs_check_degrade(stripe); /* Resets ChunkError(). */
		ClearStripeReconstruct(stripe);
		ClearStripeReconstructed(stripe);

		/*
 		 * FIXME: if write, don't endio writes in flight and don't
 		 *	  allow for new writes until userspace has updated
 		 *	  its metadata.
 		 */
	}

	/* Got to reconstruct a missing chunk. */
	if (StripeReconstruct(stripe)) {
		/*
		 * (*2*) We use StripeReconstruct() to allow for
		 *	 all chunks to be xored into the reconstructed
		 *	 one (see chunk_must_xor()).
		 */
		stripe_reconstruct(stripe);

		/*
		 * (*3*) Now we reset StripeReconstruct() and flag
		 * 	 StripeReconstructed() to show to stripe_rw(),
		 * 	 that we have reconstructed a missing chunk.
		 */
		ClearStripeReconstruct(stripe);
		SetStripeReconstructed(stripe);

		/* FIXME: reschedule to be written in case of read. */
		/* if (!RSDead && RSDegraded(rs) !StripeRBW(stripe)) {
			chunk_set(CHUNK(stripe, stripe->idx.recover), DIRTY);
			stripe_chunks_rw(stripe);
		} */

		stripe->idx.recover = -1;
	}

	/*
	 * Now that we eventually got a complete stripe, we
	 * can process the rest of the end ios on reads.
	 */
	stripe_endio(READ, stripe);

	/* End io all merged writes if not prohibited. */
	if (!RSProhibitWrites(rs) && StripeMerged(stripe)) {
		ClearStripeMerged(stripe);
		stripe_endio(WRITE_MERGED, stripe);
	}

	/* If RAID set is dead -> fail any ios to dead drives. */
	if (RSDead(rs)) {
		if (!TestSetRSDeadEndioMessage(rs))
			DMERR("RAID set dead: failing ios to dead devices");

		stripe_fail_io(stripe);
	}

	/*
	 * We have stripe references still,
	 * beacuse of read before writes or IO errors ->
	 * got to put on flush list for processing.
	 */
	if (stripe_ref(stripe)) {
		BUG_ON(!list_empty(stripe->lists + LIST_LRU));
		list_add_tail(stripe->lists + LIST_FLUSH, flush_list);
		atomic_inc(rs->stats + S_REQUEUE); /* REMOVEME: statistics. */
	} else
		stripe_lru_add(stripe);
}