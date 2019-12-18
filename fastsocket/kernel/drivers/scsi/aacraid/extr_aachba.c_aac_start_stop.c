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
struct scsi_device {TYPE_1__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {int result; int* cmnd; TYPE_3__ SCp; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;struct scsi_device* device; } ;
struct fib {int dummy; } ;
struct aac_power_management {void* parm; void* cid; void* sub; void* type; void* command; } ;
struct TYPE_5__ {int SupportedOptions2; } ;
struct aac_dev {scalar_t__ in_reset; TYPE_2__ supplement_adapter_info; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int AAC_OPTION_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  AAC_OWNER_FIRMWARE ; 
 int COMMAND_COMPLETE ; 
 int /*<<< orphan*/  CT_PM_START_UNIT ; 
 int /*<<< orphan*/  CT_PM_STOP_UNIT ; 
 int /*<<< orphan*/  CT_PM_UNIT_IMMEDIATE ; 
 int /*<<< orphan*/  CT_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int DID_OK ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int SAM_STAT_GOOD ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  VM_ContainerConfig ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ aac_start_stop_callback ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct aac_power_management* fib_data (struct fib*) ; 
 int /*<<< orphan*/  sdev_id (struct scsi_device*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_start_stop(struct scsi_cmnd *scsicmd)
{
	int status;
	struct fib *cmd_fibcontext;
	struct aac_power_management *pmcmd;
	struct scsi_device *sdev = scsicmd->device;
	struct aac_dev *aac = (struct aac_dev *)sdev->host->hostdata;

	if (!(aac->supplement_adapter_info.SupportedOptions2 &
	      AAC_OPTION_POWER_MANAGEMENT)) {
		scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8 |
				  SAM_STAT_GOOD;
		scsicmd->scsi_done(scsicmd);
		return 0;
	}

	if (aac->in_reset)
		return SCSI_MLQUEUE_HOST_BUSY;

	/*
	 *	Allocate and initialize a Fib
	 */
	cmd_fibcontext = aac_fib_alloc(aac);
	if (!cmd_fibcontext)
		return SCSI_MLQUEUE_HOST_BUSY;

	aac_fib_init(cmd_fibcontext);

	pmcmd = fib_data(cmd_fibcontext);
	pmcmd->command = cpu_to_le32(VM_ContainerConfig);
	pmcmd->type = cpu_to_le32(CT_POWER_MANAGEMENT);
	/* Eject bit ignored, not relevant */
	pmcmd->sub = (scsicmd->cmnd[4] & 1) ?
		cpu_to_le32(CT_PM_START_UNIT) : cpu_to_le32(CT_PM_STOP_UNIT);
	pmcmd->cid = cpu_to_le32(sdev_id(sdev));
	pmcmd->parm = (scsicmd->cmnd[1] & 1) ?
		cpu_to_le32(CT_PM_UNIT_IMMEDIATE) : 0;

	/*
	 *	Now send the Fib to the adapter
	 */
	status = aac_fib_send(ContainerCommand,
		  cmd_fibcontext,
		  sizeof(struct aac_power_management),
		  FsaNormal,
		  0, 1,
		  (fib_callback)aac_start_stop_callback,
		  (void *)scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	if (status == -EINPROGRESS) {
		scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
		return 0;
	}

	aac_fib_complete(cmd_fibcontext);
	aac_fib_free(cmd_fibcontext);
	return SCSI_MLQUEUE_HOST_BUSY;
}