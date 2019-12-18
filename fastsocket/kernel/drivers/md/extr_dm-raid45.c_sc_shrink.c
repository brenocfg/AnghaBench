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
struct stripe_cache {int /*<<< orphan*/  stripes; int /*<<< orphan*/  active_stripes_max; int /*<<< orphan*/  mem_cache_client; } ;
struct stripe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sc_hash_resize (struct stripe_cache*) ; 
 int /*<<< orphan*/  stripe_free (struct stripe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_hash_del (struct stripe*) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 
 struct stripe* stripe_lru_pop (struct stripe_cache*) ; 
 int /*<<< orphan*/  stripe_ref (struct stripe*) ; 

__attribute__((used)) static int sc_shrink(struct stripe_cache *sc, unsigned stripes)
{
	int r = 0;

	/* Try to get unused stripe from LRU list. */
	while (stripes--) {
		struct stripe *stripe;

		stripe = stripe_lru_pop(sc);
		if (stripe) {
			/* An LRU stripe may never have ios pending! */
			BUG_ON(stripe_io_ref(stripe));
			BUG_ON(stripe_ref(stripe));
			atomic_dec(&sc->stripes);
			/* Remove from hash if on before deletion. */
			stripe_hash_del(stripe);
			stripe_free(stripe, sc->mem_cache_client);
		} else {
			r = -ENOENT;
			break;
		}
	}

	/* Check if stats are still sane. */
	if (atomic_read(&sc->active_stripes_max) >
	    atomic_read(&sc->stripes))
		atomic_set(&sc->active_stripes_max, 0);

	if (r)
		return r;

	return atomic_read(&sc->stripes) ? sc_hash_resize(sc) : 0;
}