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
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int (* transfer_response ) (struct scsi_cmnd*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
#define  SCSI_MLQUEUE_DEVICE_BUSY 129 
#define  SCSI_MLQUEUE_HOST_BUSY 128 
 int /*<<< orphan*/  dprintk (char*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_data_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_tgt_cmd_done ; 
 struct Scsi_Host* scsi_tgt_cmd_to_host (struct scsi_cmnd*) ; 
 int stub1 (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_tgt_transfer_response(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *shost = scsi_tgt_cmd_to_host(cmd);
	int err;

	dprintk("cmd %p %u\n", cmd, rq_data_dir(cmd->request));

	err = shost->hostt->transfer_response(cmd, scsi_tgt_cmd_done);
	switch (err) {
	case SCSI_MLQUEUE_HOST_BUSY:
	case SCSI_MLQUEUE_DEVICE_BUSY:
		return -EAGAIN;
	}
	return 0;
}