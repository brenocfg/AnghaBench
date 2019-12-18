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
struct bio_vec {int dummy; } ;
struct bio_set {int /*<<< orphan*/  bvec_pool; } ;

/* Variables and functions */
 unsigned int BIOVEC_MAX_IDX ; 
 unsigned int BIOVEC_NR_POOLS ; 
 int /*<<< orphan*/  BIO_BUG_ON (int) ; 
 struct biovec_slab* bvec_slabs ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bio_vec*) ; 
 int /*<<< orphan*/  mempool_free (struct bio_vec*,int /*<<< orphan*/ ) ; 

void bvec_free_bs(struct bio_set *bs, struct bio_vec *bv, unsigned int idx)
{
	BIO_BUG_ON(idx >= BIOVEC_NR_POOLS);

	if (idx == BIOVEC_MAX_IDX)
		mempool_free(bv, bs->bvec_pool);
	else {
		struct biovec_slab *bvs = bvec_slabs + idx;

		kmem_cache_free(bvs->slab, bv);
	}
}