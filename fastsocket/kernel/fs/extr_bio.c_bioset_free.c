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
struct bio_set {scalar_t__ bio_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put_slab (struct bio_set*) ; 
 int /*<<< orphan*/  bioset_integrity_free (struct bio_set*) ; 
 int /*<<< orphan*/  biovec_free_pools (struct bio_set*) ; 
 int /*<<< orphan*/  kfree (struct bio_set*) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

void bioset_free(struct bio_set *bs)
{
	if (bs->bio_pool)
		mempool_destroy(bs->bio_pool);

	bioset_integrity_free(bs);
	biovec_free_pools(bs);
	bio_put_slab(bs);

	kfree(bs);
}