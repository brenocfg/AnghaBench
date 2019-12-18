#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_tgt_cmd {int /*<<< orphan*/  work; int /*<<< orphan*/  tag; int /*<<< orphan*/  itn_id; } ;
struct scsi_cmnd {TYPE_1__* request; } ;
struct TYPE_2__ {struct scsi_tgt_cmd* end_io_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_data_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_tgt_uspace_send_status (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_tgtd ; 

__attribute__((used)) static void scsi_tgt_cmd_done(struct scsi_cmnd *cmd)
{
	struct scsi_tgt_cmd *tcmd = cmd->request->end_io_data;

	dprintk("cmd %p %u\n", cmd, rq_data_dir(cmd->request));

	scsi_tgt_uspace_send_status(cmd, tcmd->itn_id, tcmd->tag);

	scsi_release_buffers(cmd);

	queue_work(scsi_tgtd, &tcmd->work);
}