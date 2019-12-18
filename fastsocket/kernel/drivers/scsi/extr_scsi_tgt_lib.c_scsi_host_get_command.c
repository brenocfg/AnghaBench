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
struct scsi_tgt_cmd {struct request* rq; } ;
struct scsi_cmnd {int sc_data_direction; int /*<<< orphan*/  cmnd; struct request* request; int /*<<< orphan*/  jiffies_at_alloc; } ;
struct request {struct scsi_tgt_cmd* end_io_data; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cmd_type; struct scsi_cmnd* special; int /*<<< orphan*/  cmd; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; int /*<<< orphan*/  uspace_req_q; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 struct scsi_cmnd* __scsi_get_command (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct scsi_tgt_cmd* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_tgt_cmd*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_tgt_cmd_cache ; 

struct scsi_cmnd *scsi_host_get_command(struct Scsi_Host *shost,
					enum dma_data_direction data_dir,
					gfp_t gfp_mask)
{
	int write = (data_dir == DMA_TO_DEVICE);
	struct request *rq;
	struct scsi_cmnd *cmd;
	struct scsi_tgt_cmd *tcmd;

	/* Bail if we can't get a reference to the device */
	if (!get_device(&shost->shost_gendev))
		return NULL;

	tcmd = kmem_cache_alloc(scsi_tgt_cmd_cache, GFP_ATOMIC);
	if (!tcmd)
		goto put_dev;

	/*
	 * The blk helpers are used to the READ/WRITE requests
	 * transfering data from a initiator point of view. Since
	 * we are in target mode we want the opposite.
	 */
	rq = blk_get_request(shost->uspace_req_q, !write, gfp_mask);
	if (!rq)
		goto free_tcmd;

	cmd = __scsi_get_command(shost, gfp_mask);
	if (!cmd)
		goto release_rq;

	cmd->sc_data_direction = data_dir;
	cmd->jiffies_at_alloc = jiffies;
	cmd->request = rq;

	cmd->cmnd = rq->cmd;

	rq->special = cmd;
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->cmd_flags |= REQ_TYPE_BLOCK_PC;
	rq->end_io_data = tcmd;

	tcmd->rq = rq;

	return cmd;

release_rq:
	blk_put_request(rq);
free_tcmd:
	kmem_cache_free(scsi_tgt_cmd_cache, tcmd);
put_dev:
	put_device(&shost->shost_gendev);
	return NULL;

}