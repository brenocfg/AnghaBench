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
struct dm_md_mempools {void* io_pool; void* tio_pool; int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 unsigned int DM_TYPE_BIO_BASED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MIN_IOS ; 
 int /*<<< orphan*/  _io_cache ; 
 int /*<<< orphan*/  _rq_bio_info_cache ; 
 int /*<<< orphan*/  _rq_tio_cache ; 
 int /*<<< orphan*/  _tio_cache ; 
 int /*<<< orphan*/  bioset_create (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioset_free (int /*<<< orphan*/ ) ; 
 scalar_t__ bioset_integrity_create (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct dm_md_mempools*) ; 
 struct dm_md_mempools* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (void*) ; 

struct dm_md_mempools *dm_alloc_md_mempools(unsigned type, unsigned integrity)
{
	struct dm_md_mempools *pools = kmalloc(sizeof(*pools), GFP_KERNEL);
	unsigned int pool_size = (type == DM_TYPE_BIO_BASED) ? 16 : MIN_IOS;

	if (!pools)
		return NULL;

	pools->io_pool = (type == DM_TYPE_BIO_BASED) ?
			 mempool_create_slab_pool(MIN_IOS, _io_cache) :
			 mempool_create_slab_pool(MIN_IOS, _rq_bio_info_cache);
	if (!pools->io_pool)
		goto free_pools_and_out;

	pools->tio_pool = (type == DM_TYPE_BIO_BASED) ?
			  mempool_create_slab_pool(MIN_IOS, _tio_cache) :
			  mempool_create_slab_pool(MIN_IOS, _rq_tio_cache);
	if (!pools->tio_pool)
		goto free_io_pool_and_out;

	pools->bs = bioset_create(pool_size, 0);
	if (!pools->bs)
		goto free_tio_pool_and_out;

	if (integrity && bioset_integrity_create(pools->bs, pool_size))
		goto free_bioset_and_out;

	return pools;

free_bioset_and_out:
	bioset_free(pools->bs);

free_tio_pool_and_out:
	mempool_destroy(pools->tio_pool);

free_io_pool_and_out:
	mempool_destroy(pools->io_pool);

free_pools_and_out:
	kfree(pools);

	return NULL;
}