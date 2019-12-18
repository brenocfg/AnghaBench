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
struct stripe_cache {int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  parity; } ;
struct stripe {TYPE_2__ idx; int /*<<< orphan*/  region; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int /*<<< orphan*/  rh; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ recover; struct stripe_cache sc; } ;
struct raid_address {int /*<<< orphan*/  pi; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ S_HITS_1ST ; 
 scalar_t__ S_INSCACHE ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  dm_rh_sector_to_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stripe_get (struct stripe*) ; 
 int /*<<< orphan*/  stripe_hash_del (struct stripe*) ; 
 int /*<<< orphan*/  stripe_insert (int /*<<< orphan*/ *,struct stripe*) ; 
 int /*<<< orphan*/  stripe_invalidate (struct stripe*) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 
 struct stripe* stripe_lookup (struct stripe_cache*,int /*<<< orphan*/ ) ; 
 struct stripe* stripe_lru_pop (struct stripe_cache*) ; 
 int /*<<< orphan*/  stripe_put (struct stripe*) ; 
 int /*<<< orphan*/  stripe_ref (struct stripe*) ; 

__attribute__((used)) static struct stripe *stripe_find(struct raid_set *rs,
				  struct raid_address *addr)
{
	int r;
	struct stripe_cache *sc = &rs->sc;
	struct stripe *stripe;

	/* Try stripe from hash. */
	stripe = stripe_lookup(sc, addr->key);
	if (stripe) {
		r = stripe_get(stripe);
		if (r)
			goto get_lock_failed;

		atomic_inc(rs->stats + S_HITS_1ST); /* REMOVEME: statistics. */
	} else {
		/* Not in hash -> try to get an LRU stripe. */
		stripe = stripe_lru_pop(sc);
		if (stripe) {
			/*
			 * An LRU stripe may not be referenced
			 * and may never have ios pending!
			 */
			BUG_ON(stripe_ref(stripe));
			BUG_ON(stripe_io_ref(stripe));

			/* Remove from hash if on before reuse. */
			stripe_hash_del(stripe);

			/* Invalidate before reinserting with changed key. */
			stripe_invalidate(stripe);

			stripe->key = addr->key;
			stripe->region = dm_rh_sector_to_region(rs->recover.rh,
								addr->key);
			stripe->idx.parity = addr->pi;
			r = stripe_get(stripe);
			if (r)
				goto get_lock_failed;

			/* Insert stripe into the stripe hash. */
			stripe_insert(&sc->hash, stripe);
			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_INSCACHE);
		}
	}

	return stripe;

get_lock_failed:
	stripe_put(stripe);
	return NULL;
}