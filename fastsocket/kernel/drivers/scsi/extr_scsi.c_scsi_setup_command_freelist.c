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
struct scsi_cmnd {int /*<<< orphan*/  list; } ;
struct Scsi_Host {int /*<<< orphan*/  free_list; int /*<<< orphan*/ * cmd_pool; int /*<<< orphan*/  free_list_lock; scalar_t__ unchecked_isa_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scsi_get_host_cmd_pool (int /*<<< orphan*/  const) ; 
 struct scsi_cmnd* scsi_host_alloc_command (struct Scsi_Host*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  scsi_put_host_cmd_pool (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int scsi_setup_command_freelist(struct Scsi_Host *shost)
{
	struct scsi_cmnd *cmd;
	const gfp_t gfp_mask = shost->unchecked_isa_dma ? GFP_DMA : GFP_KERNEL;

	spin_lock_init(&shost->free_list_lock);
	INIT_LIST_HEAD(&shost->free_list);

	shost->cmd_pool = scsi_get_host_cmd_pool(gfp_mask);

	if (!shost->cmd_pool)
		return -ENOMEM;

	/*
	 * Get one backup command for this host.
	 */
	cmd = scsi_host_alloc_command(shost, gfp_mask);
	if (!cmd) {
		scsi_put_host_cmd_pool(gfp_mask);
		shost->cmd_pool = NULL;
		return -ENOMEM;
	}
	list_add(&cmd->list, &shost->free_list);
	return 0;
}