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
struct scsi_device {int /*<<< orphan*/  sdev_target; int /*<<< orphan*/  queue_depth; TYPE_1__* host; } ;
struct NCR_700_Host_Parameters {int tag_negotiated; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_per_lun; scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR_700_START_TAG_NEGOTIATION ; 
 int /*<<< orphan*/  NCR_700_set_tag_neg_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_tag_type (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_set_tag_type (struct scsi_device*,int) ; 
 int /*<<< orphan*/  scsi_target_quiesce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target_resume (int /*<<< orphan*/ ) ; 
 int sdev_id (struct scsi_device*) ; 

__attribute__((used)) static int NCR_700_change_queue_type(struct scsi_device *SDp, int tag_type)
{
	int change_tag = ((tag_type ==0 &&  scsi_get_tag_type(SDp) != 0)
			  || (tag_type != 0 && scsi_get_tag_type(SDp) == 0));
	struct NCR_700_Host_Parameters *hostdata = 
		(struct NCR_700_Host_Parameters *)SDp->host->hostdata[0];

	scsi_set_tag_type(SDp, tag_type);

	/* We have a global (per target) flag to track whether TCQ is
	 * enabled, so we'll be turning it off for the entire target here.
	 * our tag algorithm will fail if we mix tagged and untagged commands,
	 * so quiesce the device before doing this */
	if (change_tag)
		scsi_target_quiesce(SDp->sdev_target);

	if (!tag_type) {
		/* shift back to the default unqueued number of commands
		 * (the user can still raise this) */
		scsi_deactivate_tcq(SDp, SDp->host->cmd_per_lun);
		hostdata->tag_negotiated &= ~(1 << sdev_id(SDp));
	} else {
		/* Here, we cleared the negotiation flag above, so this
		 * will force the driver to renegotiate */
		scsi_activate_tcq(SDp, SDp->queue_depth);
		if (change_tag)
			NCR_700_set_tag_neg_state(SDp, NCR_700_START_TAG_NEGOTIATION);
	}
	if (change_tag)
		scsi_target_resume(SDp->sdev_target);

	return tag_type;
}