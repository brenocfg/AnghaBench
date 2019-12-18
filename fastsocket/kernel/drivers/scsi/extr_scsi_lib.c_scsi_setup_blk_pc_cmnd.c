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
struct scsi_device {int dummy; } ;
struct scsi_cmnd {int transfersize; int /*<<< orphan*/  allowed; int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  sdb; } ;
struct request {int /*<<< orphan*/  retries; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  nr_phys_segments; scalar_t__ bio; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WRITE ; 
 int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 struct scsi_cmnd* scsi_get_cmd_from_req (struct scsi_device*,struct request*) ; 
 int scsi_init_io (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int scsi_prep_state_check (struct scsi_device*,struct request*) ; 
 scalar_t__ unlikely (int) ; 

int scsi_setup_blk_pc_cmnd(struct scsi_device *sdev, struct request *req)
{
	struct scsi_cmnd *cmd;
	int ret = scsi_prep_state_check(sdev, req);

	if (ret != BLKPREP_OK)
		return ret;

	cmd = scsi_get_cmd_from_req(sdev, req);
	if (unlikely(!cmd))
		return BLKPREP_DEFER;

	/*
	 * BLOCK_PC requests may transfer data, in which case they must
	 * a bio attached to them.  Or they might contain a SCSI command
	 * that does not transfer data, in which case they may optionally
	 * submit a request without an attached bio.
	 */
	if (req->bio) {
		int ret;

		BUG_ON(!req->nr_phys_segments);

		ret = scsi_init_io(cmd, GFP_ATOMIC);
		if (unlikely(ret))
			return ret;
	} else {
		BUG_ON(blk_rq_bytes(req));

		memset(&cmd->sdb, 0, sizeof(cmd->sdb));
		req->buffer = NULL;
	}

	cmd->cmd_len = req->cmd_len;
	if (!blk_rq_bytes(req))
		cmd->sc_data_direction = DMA_NONE;
	else if (rq_data_dir(req) == WRITE)
		cmd->sc_data_direction = DMA_TO_DEVICE;
	else
		cmd->sc_data_direction = DMA_FROM_DEVICE;
	
	cmd->transfersize = blk_rq_bytes(req);
	cmd->allowed = req->retries;
	return BLKPREP_OK;
}