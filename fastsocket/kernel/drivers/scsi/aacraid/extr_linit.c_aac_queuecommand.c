#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_7__ {scalar_t__ phase; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__ SCp; TYPE_4__* device; } ;
struct fib {struct scsi_cmnd* callback_data; TYPE_2__* hw_fib_va; } ;
struct aac_dev {struct fib* fibs; } ;
struct Scsi_Host {size_t can_queue; scalar_t__ hostdata; } ;
struct TYPE_8__ {struct Scsi_Host* host; } ;
struct TYPE_5__ {scalar_t__ XferState; } ;
struct TYPE_6__ {TYPE_1__ header; } ;

/* Variables and functions */
 size_t AAC_NUM_MGT_FIB ; 
 scalar_t__ AAC_OWNER_FIRMWARE ; 
 scalar_t__ AAC_OWNER_LOWLEVEL ; 
 int FAILED ; 
 scalar_t__ aac_scsi_cmd (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_queuecommand(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct Scsi_Host *host = cmd->device->host;
	struct aac_dev *dev = (struct aac_dev *)host->hostdata;
	u32 count = 0;
	cmd->scsi_done = done;
	for (; count < (host->can_queue + AAC_NUM_MGT_FIB); ++count) {
		struct fib * fib = &dev->fibs[count];
		struct scsi_cmnd * command;
		if (fib->hw_fib_va->header.XferState &&
		    ((command = fib->callback_data)) &&
		    (command == cmd) &&
		    (cmd->SCp.phase == AAC_OWNER_FIRMWARE))
			return 0; /* Already owned by Adapter */
	}
	cmd->SCp.phase = AAC_OWNER_LOWLEVEL;
	return (aac_scsi_cmd(cmd) ? FAILED : 0);
}