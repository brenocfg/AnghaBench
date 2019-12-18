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
struct request {int timeout; int retries; int /*<<< orphan*/  q; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  cmd_type; scalar_t__* cmd; int /*<<< orphan*/  cmd_len; } ;

/* Variables and functions */
 scalar_t__ ALLOW_MEDIUM_REMOVAL ; 
 int /*<<< orphan*/  COMMAND_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 int /*<<< orphan*/  REQ_TYPE_BLOCK_PC ; 
 scalar_t__ SCSI_REMOVAL_PREVENT ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_lock_door_done ; 

__attribute__((used)) static void scsi_eh_lock_door(struct scsi_device *sdev)
{
	struct request *req;

	/*
	 * blk_get_request with GFP_KERNEL (__GFP_WAIT) sleeps until a
	 * request becomes available
	 */
	req = blk_get_request(sdev->request_queue, READ, GFP_KERNEL);

	req->cmd[0] = ALLOW_MEDIUM_REMOVAL;
	req->cmd[1] = 0;
	req->cmd[2] = 0;
	req->cmd[3] = 0;
	req->cmd[4] = SCSI_REMOVAL_PREVENT;
	req->cmd[5] = 0;

	req->cmd_len = COMMAND_SIZE(req->cmd[0]);

	req->cmd_type = REQ_TYPE_BLOCK_PC;
	req->cmd_flags |= REQ_QUIET;
	req->timeout = 10 * HZ;
	req->retries = 5;

	blk_execute_rq_nowait(req->q, NULL, req, 1, eh_lock_door_done);
}