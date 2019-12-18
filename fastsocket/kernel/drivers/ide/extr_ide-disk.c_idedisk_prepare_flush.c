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
struct request_queue {TYPE_4__* queuedata; } ;
struct request {struct ide_cmd* special; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_6__ {int tf; } ;
struct TYPE_7__ {TYPE_2__ out; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct ide_cmd {struct request* rq; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tf_flags; TYPE_3__ valid; TYPE_1__ tf; } ;
struct TYPE_8__ {unsigned long capacity64; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_FLUSH ; 
 int /*<<< orphan*/  ATA_CMD_FLUSH_EXT ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IDE_TFLAG_DYN ; 
 int IDE_VALID_DEVICE ; 
 int IDE_VALID_OUT_TF ; 
 int /*<<< orphan*/  REQ_TYPE_ATA_TASKFILE ; 
 scalar_t__ ata_id_flush_ext_enabled (int /*<<< orphan*/ ) ; 
 struct ide_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ide_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void idedisk_prepare_flush(struct request_queue *q, struct request *rq)
{
	ide_drive_t *drive = q->queuedata;
	struct ide_cmd *cmd = kmalloc(sizeof(*cmd), GFP_ATOMIC);

	/* FIXME: map struct ide_taskfile on rq->cmd[] */
	BUG_ON(cmd == NULL);

	memset(cmd, 0, sizeof(*cmd));
	if (ata_id_flush_ext_enabled(drive->id) &&
	    (drive->capacity64 >= (1UL << 28)))
		cmd->tf.command = ATA_CMD_FLUSH_EXT;
	else
		cmd->tf.command = ATA_CMD_FLUSH;
	cmd->valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd->tf_flags = IDE_TFLAG_DYN;
	cmd->protocol = ATA_PROT_NODATA;

	rq->cmd_type = REQ_TYPE_ATA_TASKFILE;
	rq->special = cmd;
	cmd->rq = rq;
}