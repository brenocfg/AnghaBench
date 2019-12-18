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
struct request {int* cmd; scalar_t__ sense_len; int /*<<< orphan*/  errors; int /*<<< orphan*/  q; int /*<<< orphan*/  sense; int /*<<< orphan*/  cmd_len; } ;
struct alua_dh_data {int bufflen; scalar_t__ senselen; int /*<<< orphan*/  sense; int /*<<< orphan*/  buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  COMMAND_SIZE (int) ; 
 int EIO ; 
 int INQUIRY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  READ ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 struct request* get_alua_req (struct scsi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_vpd_inquiry(struct scsi_device *sdev, struct alua_dh_data *h)
{
	struct request *rq;
	int err = SCSI_DH_RES_TEMP_UNAVAIL;

	rq = get_alua_req(sdev, h->buff, h->bufflen, READ);
	if (!rq)
		goto done;

	/* Prepare the command. */
	rq->cmd[0] = INQUIRY;
	rq->cmd[1] = 1;
	rq->cmd[2] = 0x83;
	rq->cmd[4] = h->bufflen;
	rq->cmd_len = COMMAND_SIZE(INQUIRY);

	rq->sense = h->sense;
	memset(rq->sense, 0, SCSI_SENSE_BUFFERSIZE);
	rq->sense_len = h->senselen = 0;

	err = blk_execute_rq(rq->q, NULL, rq, 1);
	if (err == -EIO) {
		sdev_printk(KERN_INFO, sdev,
			    "%s: evpd inquiry failed with %x\n",
			    ALUA_DH_NAME, rq->errors);
		h->senselen = rq->sense_len;
		err = SCSI_DH_IO;
	}
	blk_put_request(rq);
done:
	return err;
}