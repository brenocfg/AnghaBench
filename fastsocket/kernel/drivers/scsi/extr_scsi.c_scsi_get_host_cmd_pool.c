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
struct scsi_host_cmd_pool {int /*<<< orphan*/  users; void* cmd_slab; void* sense_slab; int /*<<< orphan*/  slab_flags; int /*<<< orphan*/  sense_name; int /*<<< orphan*/  cmd_name; } ;
struct scsi_cmnd {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int SCSI_SENSE_BUFFERSIZE ; 
 int __GFP_DMA ; 
 int /*<<< orphan*/  host_cmd_pool_mutex ; 
 void* kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct scsi_host_cmd_pool scsi_cmd_dma_pool ; 
 struct scsi_host_cmd_pool scsi_cmd_pool ; 

__attribute__((used)) static struct scsi_host_cmd_pool *scsi_get_host_cmd_pool(gfp_t gfp_mask)
{
	struct scsi_host_cmd_pool *retval = NULL, *pool;
	/*
	 * Select a command slab for this host and create it if not
	 * yet existent.
	 */
	mutex_lock(&host_cmd_pool_mutex);
	pool = (gfp_mask & __GFP_DMA) ? &scsi_cmd_dma_pool :
		&scsi_cmd_pool;
	if (!pool->users) {
		pool->cmd_slab = kmem_cache_create(pool->cmd_name,
						   sizeof(struct scsi_cmnd), 0,
						   pool->slab_flags, NULL);
		if (!pool->cmd_slab)
			goto fail;

		pool->sense_slab = kmem_cache_create(pool->sense_name,
						     SCSI_SENSE_BUFFERSIZE, 0,
						     pool->slab_flags, NULL);
		if (!pool->sense_slab) {
			kmem_cache_destroy(pool->cmd_slab);
			goto fail;
		}
	}

	pool->users++;
	retval = pool;
 fail:
	mutex_unlock(&host_cmd_pool_mutex);
	return retval;
}