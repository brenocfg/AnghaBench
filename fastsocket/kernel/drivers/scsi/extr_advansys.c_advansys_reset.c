#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_7__ {scalar_t__ err_code; } ;
struct TYPE_6__ {int /*<<< orphan*/  adv_dvc_var; TYPE_3__ asc_dvc_var; } ;
struct asc_board {int /*<<< orphan*/  last_reset; TYPE_2__ dvc_var; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {struct Scsi_Host* host; } ;
typedef  TYPE_3__ ASC_DVC_VAR ;
typedef  int /*<<< orphan*/  ADV_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_DBG (int,char*,...) ; 
#define  ASC_FALSE 129 
 scalar_t__ ASC_NARROW_BOARD (struct asc_board*) ; 
 int /*<<< orphan*/  ASC_STATS (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
#define  ASC_TRUE 128 
 int /*<<< orphan*/  AdvISR (int /*<<< orphan*/ *) ; 
 int AdvResetChipAndSB (int /*<<< orphan*/ *) ; 
 int AscInitAsc1000Driver (TYPE_3__*) ; 
 int FAILED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,...) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int advansys_reset(struct scsi_cmnd *scp)
{
	struct Scsi_Host *shost = scp->device->host;
	struct asc_board *boardp = shost_priv(shost);
	unsigned long flags;
	int status;
	int ret = SUCCESS;

	ASC_DBG(1, "0x%p\n", scp);

	ASC_STATS(shost, reset);

	scmd_printk(KERN_INFO, scp, "SCSI bus reset started...\n");

	if (ASC_NARROW_BOARD(boardp)) {
		ASC_DVC_VAR *asc_dvc = &boardp->dvc_var.asc_dvc_var;

		/* Reset the chip and SCSI bus. */
		ASC_DBG(1, "before AscInitAsc1000Driver()\n");
		status = AscInitAsc1000Driver(asc_dvc);

		/* Refer to ASC_IERR_* defintions for meaning of 'err_code'. */
		if (asc_dvc->err_code) {
			scmd_printk(KERN_INFO, scp, "SCSI bus reset error: "
				    "0x%x\n", asc_dvc->err_code);
			ret = FAILED;
		} else if (status) {
			scmd_printk(KERN_INFO, scp, "SCSI bus reset warning: "
				    "0x%x\n", status);
		} else {
			scmd_printk(KERN_INFO, scp, "SCSI bus reset "
				    "successful\n");
		}

		ASC_DBG(1, "after AscInitAsc1000Driver()\n");
		spin_lock_irqsave(shost->host_lock, flags);
	} else {
		/*
		 * If the suggest reset bus flags are set, then reset the bus.
		 * Otherwise only reset the device.
		 */
		ADV_DVC_VAR *adv_dvc = &boardp->dvc_var.adv_dvc_var;

		/*
		 * Reset the target's SCSI bus.
		 */
		ASC_DBG(1, "before AdvResetChipAndSB()\n");
		switch (AdvResetChipAndSB(adv_dvc)) {
		case ASC_TRUE:
			scmd_printk(KERN_INFO, scp, "SCSI bus reset "
				    "successful\n");
			break;
		case ASC_FALSE:
		default:
			scmd_printk(KERN_INFO, scp, "SCSI bus reset error\n");
			ret = FAILED;
			break;
		}
		spin_lock_irqsave(shost->host_lock, flags);
		AdvISR(adv_dvc);
	}

	/* Save the time of the most recently completed reset. */
	boardp->last_reset = jiffies;
	spin_unlock_irqrestore(shost->host_lock, flags);

	ASC_DBG(1, "ret %d\n", ret);

	return ret;
}