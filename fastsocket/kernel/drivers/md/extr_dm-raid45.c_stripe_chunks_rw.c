#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stripe_cache {int /*<<< orphan*/  active_stripes_max; } ;
struct stripe {int /*<<< orphan*/  sc; } ;
struct raid_set {scalar_t__ stats; struct stripe_cache sc; } ;

/* Variables and functions */
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ S_FLUSHS ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int for_each_io_dev (struct stripe*,int /*<<< orphan*/ ) ; 
 int sc_active (struct stripe_cache*) ; 
 int /*<<< orphan*/  stripe_chunk_rw ; 
 int /*<<< orphan*/  stripe_get_references ; 

__attribute__((used)) static int stripe_chunks_rw(struct stripe *stripe)
{
	int r;
	struct raid_set *rs = RS(stripe->sc);

	/*
	 * Increment the pending count on the stripe
	 * first, so that we don't race in endio().
	 *
	 * An inc (IO) is needed for any chunk unless !ChunkIo(chunk):
	 *
	 * o not uptodate
	 * o dirtied by writes merged
	 * o dirtied by parity calculations
	 */
	r = for_each_io_dev(stripe, stripe_get_references);
	if (r) {
		/* Io needed: chunks are either not uptodate or dirty. */
		int max;	/* REMOVEME: */
		struct stripe_cache *sc = &rs->sc;

		/* Submit actual io. */
		for_each_io_dev(stripe, stripe_chunk_rw);

		/* REMOVEME: statistics */
		max = sc_active(sc);
		if (atomic_read(&sc->active_stripes_max) < max)
			atomic_set(&sc->active_stripes_max, max);

		atomic_inc(rs->stats + S_FLUSHS);
		/* END REMOVEME: statistics */
	}

	return r;
}