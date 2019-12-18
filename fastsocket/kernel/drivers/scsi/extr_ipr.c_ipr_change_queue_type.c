#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/  queue_depth; scalar_t__ tagged_supported; scalar_t__ hostdata; TYPE_2__* host; } ;
struct ipr_resource_entry {int dummy; } ;
struct ipr_ioa_cfg {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ ipr_is_gscsi (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_tag_type (struct scsi_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ipr_change_queue_type(struct scsi_device *sdev, int tag_type)
{
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)sdev->host->hostdata;
	struct ipr_resource_entry *res;
	unsigned long lock_flags = 0;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (struct ipr_resource_entry *)sdev->hostdata;

	if (res) {
		if (ipr_is_gscsi(res) && sdev->tagged_supported) {
			/*
			 * We don't bother quiescing the device here since the
			 * adapter firmware does it for us.
			 */
			scsi_set_tag_type(sdev, tag_type);

			if (tag_type)
				scsi_activate_tcq(sdev, sdev->queue_depth);
			else
				scsi_deactivate_tcq(sdev, sdev->queue_depth);
		} else
			tag_type = 0;
	} else
		tag_type = 0;

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return tag_type;
}