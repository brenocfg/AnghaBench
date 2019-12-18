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
struct request {int* cmd; int* sense; int /*<<< orphan*/  q; struct alua_dh_data* end_io_data; scalar_t__ sense_len; int /*<<< orphan*/  cmd_len; } ;
struct alua_dh_data {int* buff; int group_id; int* sense; scalar_t__ senselen; struct scsi_device* sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_SIZE (int) ; 
 int MAINTENANCE_OUT ; 
 int MO_SET_TARGET_PGS ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 int SCSI_SENSE_BUFFERSIZE ; 
 int TPGS_STATE_OPTIMIZED ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int,int /*<<< orphan*/ ) ; 
 struct request* get_alua_req (struct scsi_device*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stpg_endio ; 

__attribute__((used)) static unsigned submit_stpg(struct alua_dh_data *h)
{
	struct request *rq;
	int stpg_len = 8;
	struct scsi_device *sdev = h->sdev;

	/* Prepare the data buffer */
	memset(h->buff, 0, stpg_len);
	h->buff[4] = TPGS_STATE_OPTIMIZED & 0x0f;
	h->buff[6] = (h->group_id >> 8) & 0xff;
	h->buff[7] = h->group_id & 0xff;

	rq = get_alua_req(sdev, h->buff, stpg_len, WRITE);
	if (!rq)
		return SCSI_DH_RES_TEMP_UNAVAIL;

	/* Prepare the command. */
	rq->cmd[0] = MAINTENANCE_OUT;
	rq->cmd[1] = MO_SET_TARGET_PGS;
	rq->cmd[6] = (stpg_len >> 24) & 0xff;
	rq->cmd[7] = (stpg_len >> 16) & 0xff;
	rq->cmd[8] = (stpg_len >>  8) & 0xff;
	rq->cmd[9] = stpg_len & 0xff;
	rq->cmd_len = COMMAND_SIZE(MAINTENANCE_OUT);

	rq->sense = h->sense;
	memset(rq->sense, 0, SCSI_SENSE_BUFFERSIZE);
	rq->sense_len = h->senselen = 0;
	rq->end_io_data = h;

	blk_execute_rq_nowait(rq->q, NULL, rq, 1, stpg_endio);
	return SCSI_DH_OK;
}