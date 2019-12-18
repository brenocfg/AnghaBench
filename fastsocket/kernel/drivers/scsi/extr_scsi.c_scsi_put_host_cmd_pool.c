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
struct scsi_host_cmd_pool {scalar_t__ users; int /*<<< orphan*/  sense_slab; int /*<<< orphan*/  cmd_slab; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __GFP_DMA ; 
 int /*<<< orphan*/  host_cmd_pool_mutex ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scsi_host_cmd_pool scsi_cmd_dma_pool ; 
 struct scsi_host_cmd_pool scsi_cmd_pool ; 

__attribute__((used)) static void scsi_put_host_cmd_pool(gfp_t gfp_mask)
{
	struct scsi_host_cmd_pool *pool;

	mutex_lock(&host_cmd_pool_mutex);
	pool = (gfp_mask & __GFP_DMA) ? &scsi_cmd_dma_pool :
		&scsi_cmd_pool;
	/*
	 * This may happen if a driver has a mismatched get and put
	 * of the command pool; the driver should be implicated in
	 * the stack trace
	 */
	BUG_ON(pool->users == 0);

	if (!--pool->users) {
		kmem_cache_destroy(pool->cmd_slab);
		kmem_cache_destroy(pool->sense_slab);
	}
	mutex_unlock(&host_cmd_pool_mutex);
}