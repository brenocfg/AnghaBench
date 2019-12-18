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
struct TYPE_2__ {int /*<<< orphan*/ * cache; } ;
struct stripe_cache {int /*<<< orphan*/  hash; scalar_t__ dm_io_client; scalar_t__ mem_cache_client; TYPE_1__ kc; int /*<<< orphan*/  stripes; } ;
struct raid_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 struct raid_set* RS (struct stripe_cache*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_io_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dm_mem_cache_client_destroy (scalar_t__) ; 
 int /*<<< orphan*/  hash_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_shrink (struct stripe_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_recover_free (struct raid_set*) ; 

__attribute__((used)) static void sc_exit(struct stripe_cache *sc)
{
	struct raid_set *rs = RS(sc);

	if (sc->kc.cache) {
		stripe_recover_free(rs);
		BUG_ON(sc_shrink(sc, atomic_read(&sc->stripes)));
		kmem_cache_destroy(sc->kc.cache);
		sc->kc.cache = NULL;

		if (sc->mem_cache_client && !IS_ERR(sc->mem_cache_client))
			dm_mem_cache_client_destroy(sc->mem_cache_client);

		if (sc->dm_io_client && !IS_ERR(sc->dm_io_client))
			dm_io_client_destroy(sc->dm_io_client);

		hash_exit(&sc->hash);
	}
}