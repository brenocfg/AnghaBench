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
struct scsi_host_cmd_pool {int /*<<< orphan*/  cmd_slab; int /*<<< orphan*/  sense_slab; } ;
struct scsi_cmnd {struct scsi_cmnd* sense_buffer; struct scsi_cmnd* prot_sdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 

__attribute__((used)) static void
scsi_pool_free_command(struct scsi_host_cmd_pool *pool,
			 struct scsi_cmnd *cmd)
{
	if (cmd->prot_sdb)
		kmem_cache_free(scsi_sdb_cache, cmd->prot_sdb);

	kmem_cache_free(pool->sense_slab, cmd->sense_buffer);
	kmem_cache_free(pool->cmd_slab, cmd);
}