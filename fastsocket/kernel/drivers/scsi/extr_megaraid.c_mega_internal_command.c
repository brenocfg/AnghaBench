#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/  host; } ;
struct TYPE_13__ {int /*<<< orphan*/  idx; int /*<<< orphan*/ * pthru; int /*<<< orphan*/  raw_mbox; TYPE_4__* cmd; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ scb_t ;
struct TYPE_14__ {scalar_t__ cmd; int status; int /*<<< orphan*/  subopcode; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_2__ megacmd_t ;
typedef  int /*<<< orphan*/  mega_passthru ;
struct TYPE_15__ {int /*<<< orphan*/  int_mtx; int /*<<< orphan*/  int_waitq; int /*<<< orphan*/  host; TYPE_1__* int_cdb; TYPE_1__ int_scb; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_16__ {int result; TYPE_1__* cmnd; void* host_scribble; struct scsi_device* device; } ;
typedef  TYPE_4__ Scsi_Cmnd ;

/* Variables and functions */
 int /*<<< orphan*/  CMDID_INT_CMDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ MEGA_INTERNAL_CMD ; 
 scalar_t__ MEGA_MBOXCMD_PASSTHRU ; 
 int /*<<< orphan*/  SCB_ACTIVE ; 
 int /*<<< orphan*/  kfree (struct scsi_device*) ; 
 struct scsi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mega_internal_done ; 
 int /*<<< orphan*/  megaraid_queue (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* scsi_allocate_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_free_command (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ trace_level ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mega_internal_command(adapter_t *adapter, megacmd_t *mc, mega_passthru *pthru)
{
	Scsi_Cmnd	*scmd;
	struct	scsi_device *sdev;
	scb_t	*scb;
	int	rval;

	scmd = scsi_allocate_command(GFP_KERNEL);
	if (!scmd)
		return -ENOMEM;

	/*
	 * The internal commands share one command id and hence are
	 * serialized. This is so because we want to reserve maximum number of
	 * available command ids for the I/O commands.
	 */
	mutex_lock(&adapter->int_mtx);

	scb = &adapter->int_scb;
	memset(scb, 0, sizeof(scb_t));

	sdev = kzalloc(sizeof(struct scsi_device), GFP_KERNEL);
	scmd->device = sdev;

	memset(adapter->int_cdb, 0, sizeof(adapter->int_cdb));
	scmd->cmnd = adapter->int_cdb;
	scmd->device->host = adapter->host;
	scmd->host_scribble = (void *)scb;
	scmd->cmnd[0] = MEGA_INTERNAL_CMD;

	scb->state |= SCB_ACTIVE;
	scb->cmd = scmd;

	memcpy(scb->raw_mbox, mc, sizeof(megacmd_t));

	/*
	 * Is it a passthru command
	 */
	if( mc->cmd == MEGA_MBOXCMD_PASSTHRU ) {

		scb->pthru = pthru;
	}

	scb->idx = CMDID_INT_CMDS;

	megaraid_queue(scmd, mega_internal_done);

	wait_for_completion(&adapter->int_waitq);

	rval = scmd->result;
	mc->status = scmd->result;
	kfree(sdev);

	/*
	 * Print a debug message for all failed commands. Applications can use
	 * this information.
	 */
	if( scmd->result && trace_level ) {
		printk("megaraid: cmd [%x, %x, %x] status:[%x]\n",
			mc->cmd, mc->opcode, mc->subopcode, scmd->result);
	}

	mutex_unlock(&adapter->int_mtx);

	scsi_free_command(GFP_KERNEL, scmd);

	return rval;
}