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
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {scalar_t__ ei; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearStripeReconstruct (struct stripe*) ; 
 int /*<<< orphan*/  ClearStripeReconstructed (struct stripe*) ; 
 int EBUSY ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ RSDead (struct raid_set*) ; 
 int /*<<< orphan*/  RSDegraded (struct raid_set*) ; 
 scalar_t__ RSEnforceParityCreation (struct raid_set*) ; 
 scalar_t__ S_DEGRADED ; 
 scalar_t__ S_NOSYNC ; 
 scalar_t__ S_RECONSTRUCTED ; 
 scalar_t__ S_RECONSTRUCT_SET ; 
 scalar_t__ StripeReconstruct (struct stripe*) ; 
 scalar_t__ StripeReconstructed (struct stripe*) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int dev_for_parity (struct stripe*,int*) ; 
 int /*<<< orphan*/  stripe_allow_io (struct stripe*) ; 
 int stripe_chunk_set_io_flags (struct stripe*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stripe_check_reconstruct(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);

	if (RSDead(rs)) {
		ClearStripeReconstruct(stripe);
		ClearStripeReconstructed(stripe);
		stripe_allow_io(stripe);
		return 0;
	}

	/* Avoid further reconstruction setting, when already set. */
	if (StripeReconstruct(stripe)) {
		/* REMOVEME: statistics. */
		atomic_inc(rs->stats + S_RECONSTRUCT_SET);
		return -EBUSY;
	}

	/* Initially allow io on all chunks. */
	stripe_allow_io(stripe);

	/* Return if stripe is already reconstructed. */
	if (StripeReconstructed(stripe)) {
		atomic_inc(rs->stats + S_RECONSTRUCTED);
		return 0;
	}

	/*
	 * Degraded/reconstruction mode (device failed) ->
	 * avoid io on the failed device.
	 */
	if (unlikely(RSDegraded(rs))) {
		/* REMOVEME: statistics. */
		atomic_inc(rs->stats + S_DEGRADED);
		/* Allow IO on all devices but the dead one. */
		BUG_ON(rs->set.ei < 0);
		return stripe_chunk_set_io_flags(stripe, rs->set.ei);
	} else {
		int sync, pi = dev_for_parity(stripe, &sync);

		/*
		 * Reconstruction mode (ie. a particular (replaced) device or
		 * some (rotating) parity chunk is being resynchronized) ->
		 *   o make sure all needed chunks are read in
		 *   o cope with 3/4 disk array special case where it
		 *     doesn't make a difference to read in parity
		 *     to xor data in/out
		 */
		if (RSEnforceParityCreation(rs) || !sync) {
			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_NOSYNC);
			/* Allow IO on all devs but the one to reconstruct. */
			return stripe_chunk_set_io_flags(stripe, pi);
		}
	}

	return 0;
}