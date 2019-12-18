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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;
struct request {int* cmd; scalar_t__ sense_len; int /*<<< orphan*/  sense; int /*<<< orphan*/  cmd_len; } ;
struct rdac_dh_data {int /*<<< orphan*/  sense; int /*<<< orphan*/  inq; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_SIZE (int) ; 
 int EIO ; 
 int INQUIRY ; 
 int /*<<< orphan*/  READ ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 struct request* get_rdac_req (struct scsi_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_inquiry(struct scsi_device *sdev, int page_code,
			  unsigned int len, struct rdac_dh_data *h)
{
	struct request *rq;
	struct request_queue *q = sdev->request_queue;
	int err = SCSI_DH_RES_TEMP_UNAVAIL;

	rq = get_rdac_req(sdev, &h->inq, len, READ);
	if (!rq)
		goto done;

	/* Prepare the command. */
	rq->cmd[0] = INQUIRY;
	rq->cmd[1] = 1;
	rq->cmd[2] = page_code;
	rq->cmd[4] = len;
	rq->cmd_len = COMMAND_SIZE(INQUIRY);

	rq->sense = h->sense;
	memset(rq->sense, 0, SCSI_SENSE_BUFFERSIZE);
	rq->sense_len = 0;

	err = blk_execute_rq(q, NULL, rq, 1);
	if (err == -EIO)
		err = SCSI_DH_IO;

	blk_put_request(rq);
done:
	return err;
}