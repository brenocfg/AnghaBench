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
struct scsi_host_cmd_pool {int gfp_mask; int /*<<< orphan*/  cmd_slab; int /*<<< orphan*/  sense_slab; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 struct scsi_cmnd* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct scsi_cmnd *
scsi_pool_alloc_command(struct scsi_host_cmd_pool *pool, gfp_t gfp_mask)
{
	struct scsi_cmnd *cmd;

	cmd = kmem_cache_zalloc(pool->cmd_slab, gfp_mask | pool->gfp_mask);
	if (!cmd)
		return NULL;

	cmd->sense_buffer = kmem_cache_alloc(pool->sense_slab,
					     gfp_mask | pool->gfp_mask);
	if (!cmd->sense_buffer) {
		kmem_cache_free(pool->cmd_slab, cmd);
		return NULL;
	}

	return cmd;
}