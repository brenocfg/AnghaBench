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
struct scsi_cmnd {int /*<<< orphan*/  prot_op; int /*<<< orphan*/  cmnd; struct request* request; int /*<<< orphan*/  tag; } ;
struct request {int /*<<< orphan*/  cmd; int /*<<< orphan*/  tag; struct scsi_cmnd* special; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCSI_PROT_NORMAL ; 
 struct scsi_cmnd* scsi_get_command (struct scsi_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct scsi_cmnd *scsi_get_cmd_from_req(struct scsi_device *sdev,
		struct request *req)
{
	struct scsi_cmnd *cmd;

	if (!req->special) {
		cmd = scsi_get_command(sdev, GFP_ATOMIC);
		if (unlikely(!cmd))
			return NULL;
		req->special = cmd;
	} else {
		cmd = req->special;
	}

	/* pull a tag out of the request if we have one */
	cmd->tag = req->tag;
	cmd->request = req;

	cmd->cmnd = req->cmd;
	cmd->prot_op = SCSI_PROT_NORMAL;

	return cmd;
}