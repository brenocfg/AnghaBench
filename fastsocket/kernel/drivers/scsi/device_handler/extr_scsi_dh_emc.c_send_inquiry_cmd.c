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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct request {int* cmd; scalar_t__ sense_len; int /*<<< orphan*/  errors; int /*<<< orphan*/  sense; } ;
struct clariion_dh_data {scalar_t__ senselen; int /*<<< orphan*/  sense; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_NAME ; 
 int EIO ; 
 int INQUIRY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 struct request* get_req (struct scsi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_inquiry_cmd(struct scsi_device *sdev, int page,
			    struct clariion_dh_data *csdev)
{
	struct request *rq = get_req(sdev, INQUIRY, csdev->buffer);
	int err;

	if (!rq)
		return SCSI_DH_RES_TEMP_UNAVAIL;

	rq->sense = csdev->sense;
	memset(rq->sense, 0, SCSI_SENSE_BUFFERSIZE);
	rq->sense_len = csdev->senselen = 0;

	rq->cmd[0] = INQUIRY;
	if (page != 0) {
		rq->cmd[1] = 1;
		rq->cmd[2] = page;
	}
	err = blk_execute_rq(sdev->request_queue, NULL, rq, 1);
	if (err == -EIO) {
		sdev_printk(KERN_INFO, sdev,
			    "%s: failed to send %s INQUIRY: %x\n",
			    CLARIION_NAME, page?"EVPD":"standard",
			    rq->errors);
		csdev->senselen = rq->sense_len;
		err = SCSI_DH_IO;
	}

	blk_put_request(rq);

	return err;
}