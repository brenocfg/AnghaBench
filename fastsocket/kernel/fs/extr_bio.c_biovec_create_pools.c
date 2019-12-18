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
struct biovec_slab {int /*<<< orphan*/  slab; } ;
struct bio_set {int /*<<< orphan*/  bvec_pool; } ;

/* Variables and functions */
 int BIOVEC_MAX_IDX ; 
 int ENOMEM ; 
 struct biovec_slab* bvec_slabs ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int biovec_create_pools(struct bio_set *bs, int pool_entries)
{
	struct biovec_slab *bp = bvec_slabs + BIOVEC_MAX_IDX;

	bs->bvec_pool = mempool_create_slab_pool(pool_entries, bp->slab);
	if (!bs->bvec_pool)
		return -ENOMEM;

	return 0;
}