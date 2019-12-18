#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct srp_cmd {int task_attr; scalar_t__ tag; int /*<<< orphan*/  lun; int /*<<< orphan*/ * cdb; } ;
struct scsi_lun {int dummy; } ;
struct TYPE_5__ {void* sgl; } ;
struct TYPE_6__ {int length; TYPE_2__ table; } ;
struct TYPE_4__ {void* ptr; } ;
struct scsi_cmnd {int tag; TYPE_3__ sdb; int /*<<< orphan*/  cmnd; TYPE_1__ SCp; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int MSG_HEAD_TAG ; 
 int MSG_ORDERED_TAG ; 
 int MSG_SIMPLE_TAG ; 
#define  SRP_HEAD_TASK 130 
#define  SRP_ORDERED_TASK 129 
#define  SRP_SIMPLE_TASK 128 
 int /*<<< orphan*/  dprintk (char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned long long) ; 
 int /*<<< orphan*/  eprintk (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* scsi_host_get_command (struct Scsi_Host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put_command (struct Scsi_Host*,struct scsi_cmnd*) ; 
 int scsi_tgt_queue_command (struct scsi_cmnd*,scalar_t__,struct scsi_lun*,scalar_t__) ; 
 int srp_cmd_direction (struct srp_cmd*) ; 
 int vscsis_data_length (struct srp_cmd*,int) ; 

int srp_cmd_queue(struct Scsi_Host *shost, struct srp_cmd *cmd, void *info,
		  u64 itn_id, u64 addr)
{
	enum dma_data_direction dir;
	struct scsi_cmnd *sc;
	int tag, len, err;

	switch (cmd->task_attr) {
	case SRP_SIMPLE_TASK:
		tag = MSG_SIMPLE_TAG;
		break;
	case SRP_ORDERED_TASK:
		tag = MSG_ORDERED_TAG;
		break;
	case SRP_HEAD_TASK:
		tag = MSG_HEAD_TAG;
		break;
	default:
		eprintk("Task attribute %d not supported\n", cmd->task_attr);
		tag = MSG_ORDERED_TAG;
	}

	dir = srp_cmd_direction(cmd);
	len = vscsis_data_length(cmd, dir);

	dprintk("%p %x %lx %d %d %d %llx\n", info, cmd->cdb[0],
		cmd->lun, dir, len, tag, (unsigned long long) cmd->tag);

	sc = scsi_host_get_command(shost, dir, GFP_KERNEL);
	if (!sc)
		return -ENOMEM;

	sc->SCp.ptr = info;
	memcpy(sc->cmnd, cmd->cdb, MAX_COMMAND_SIZE);
	sc->sdb.length = len;
	sc->sdb.table.sgl = (void *) (unsigned long) addr;
	sc->tag = tag;
	err = scsi_tgt_queue_command(sc, itn_id, (struct scsi_lun *)&cmd->lun,
				     cmd->tag);
	if (err)
		scsi_host_put_command(shost, sc);

	return err;
}