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
struct request {unsigned char* sense; int retries; int timeout; int cmd_flags; unsigned int resid_len; int errors; int /*<<< orphan*/  q; int /*<<< orphan*/  cmd_type; scalar_t__ sense_len; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_SIZE (unsigned char const) ; 
 int DMA_TO_DEVICE ; 
 int DRIVER_ERROR ; 
 int REQ_PREEMPT ; 
 int REQ_QUIET ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int scsi_execute(struct scsi_device *sdev, const unsigned char *cmd,
		 int data_direction, void *buffer, unsigned bufflen,
		 unsigned char *sense, int timeout, int retries, int flags,
		 int *resid)
{
	struct request *req;
	int write = (data_direction == DMA_TO_DEVICE);
	int ret = DRIVER_ERROR << 24;

	req = blk_get_request(sdev->request_queue, write, __GFP_WAIT);
	if (!req)
		return ret;

	if (bufflen &&	blk_rq_map_kern(sdev->request_queue, req,
					buffer, bufflen, __GFP_WAIT))
		goto out;

	req->cmd_len = COMMAND_SIZE(cmd[0]);
	memcpy(req->cmd, cmd, req->cmd_len);
	req->sense = sense;
	req->sense_len = 0;
	req->retries = retries;
	req->timeout = timeout;
	req->cmd_type = REQ_TYPE_BLOCK_PC;
	req->cmd_flags |= flags | REQ_QUIET | REQ_PREEMPT;

	/*
	 * head injection *required* here otherwise quiesce won't work
	 */
	blk_execute_rq(req->q, NULL, req, 1);

	/*
	 * Some devices (USB mass-storage in particular) may transfer
	 * garbage data together with a residue indicating that the data
	 * is invalid.  Prevent the garbage from being misinterpreted
	 * and prevent security leaks by zeroing out the excess data.
	 */
	if (unlikely(req->resid_len > 0 && req->resid_len <= bufflen))
		memset(buffer + (bufflen - req->resid_len), 0, req->resid_len);

	if (resid)
		*resid = req->resid_len;
	ret = req->errors;
 out:
	blk_put_request(req);

	return ret;
}