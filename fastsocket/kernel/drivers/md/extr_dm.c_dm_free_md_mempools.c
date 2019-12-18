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
struct dm_md_mempools {scalar_t__ bs; scalar_t__ tio_pool; scalar_t__ io_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_free (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dm_md_mempools*) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

void dm_free_md_mempools(struct dm_md_mempools *pools)
{
	if (!pools)
		return;

	if (pools->io_pool)
		mempool_destroy(pools->io_pool);

	if (pools->tio_pool)
		mempool_destroy(pools->tio_pool);

	if (pools->bs)
		bioset_free(pools->bs);

	kfree(pools);
}