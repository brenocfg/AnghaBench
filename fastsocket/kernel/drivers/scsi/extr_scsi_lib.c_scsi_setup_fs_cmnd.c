#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {TYPE_2__* scsi_dh_data; } ;
struct scsi_cmnd {int /*<<< orphan*/  cmnd; } ;
struct request {int /*<<< orphan*/  nr_phys_segments; } ;
struct TYPE_4__ {TYPE_1__* scsi_dh; } ;
struct TYPE_3__ {int (* prep_fn ) (struct scsi_device*,struct request*) ;} ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BLK_MAX_CDB ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* scsi_get_cmd_from_req (struct scsi_device*,struct request*) ; 
 int scsi_init_io (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int scsi_prep_state_check (struct scsi_device*,struct request*) ; 
 int stub1 (struct scsi_device*,struct request*) ; 
 scalar_t__ unlikely (int) ; 

int scsi_setup_fs_cmnd(struct scsi_device *sdev, struct request *req)
{
	struct scsi_cmnd *cmd;
	int ret = scsi_prep_state_check(sdev, req);

	if (ret != BLKPREP_OK)
		return ret;

	if (unlikely(sdev->scsi_dh_data && sdev->scsi_dh_data->scsi_dh
			 && sdev->scsi_dh_data->scsi_dh->prep_fn)) {
		ret = sdev->scsi_dh_data->scsi_dh->prep_fn(sdev, req);
		if (ret != BLKPREP_OK)
			return ret;
	}

	/*
	 * Filesystem requests must transfer data.
	 */
	BUG_ON(!req->nr_phys_segments);

	cmd = scsi_get_cmd_from_req(sdev, req);
	if (unlikely(!cmd))
		return BLKPREP_DEFER;

	memset(cmd->cmnd, 0, BLK_MAX_CDB);
	return scsi_init_io(cmd, GFP_ATOMIC);
}