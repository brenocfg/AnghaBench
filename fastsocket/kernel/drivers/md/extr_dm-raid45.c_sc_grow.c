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
struct stripe_cache {int /*<<< orphan*/  stripes; int /*<<< orphan*/  mem_cache_client; } ;
struct stripe {int dummy; } ;
typedef  enum grow { ____Placeholder_grow } grow ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct stripe*) ; 
 int sc_hash_resize (struct stripe_cache*) ; 
 struct stripe* stripe_alloc (struct stripe_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stripe_lru_add (struct stripe*) ; 

__attribute__((used)) static int sc_grow(struct stripe_cache *sc, unsigned stripes, enum grow grow)
{
	int r = 0;

	/* Try to allocate this many (additional) stripes. */
	while (stripes--) {
		struct stripe *stripe =
			stripe_alloc(sc, sc->mem_cache_client, grow);

		if (likely(stripe)) {
			stripe_lru_add(stripe);
			atomic_inc(&sc->stripes);
		} else {
			r = -ENOMEM;
			break;
		}
	}

	return r ? r : sc_hash_resize(sc);
}