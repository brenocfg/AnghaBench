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
struct scsi_cmnd {TYPE_3__* device; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int (* eh_target_reset_handler ) (struct scsi_cmnd*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; TYPE_2__* hostt; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  __scsi_report_device_reset ; 
 int /*<<< orphan*/  __starget_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int scsi_try_target_reset(struct scsi_cmnd *scmd)
{
	unsigned long flags;
	int rtn;

	if (!scmd->device->host->hostt->eh_target_reset_handler)
		return FAILED;

	rtn = scmd->device->host->hostt->eh_target_reset_handler(scmd);
	if (rtn == SUCCESS) {
		spin_lock_irqsave(scmd->device->host->host_lock, flags);
		__starget_for_each_device(scsi_target(scmd->device), NULL,
					  __scsi_report_device_reset);
		spin_unlock_irqrestore(scmd->device->host->host_lock, flags);
	}

	return rtn;
}