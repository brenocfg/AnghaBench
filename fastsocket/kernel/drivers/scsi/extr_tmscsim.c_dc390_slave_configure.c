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
struct scsi_device {scalar_t__ tagged_supported; scalar_t__ hostdata; TYPE_1__* host; } ;
struct dc390_dcb {int DevMode; int /*<<< orphan*/  SyncMode; } ;
struct dc390_acb {int /*<<< orphan*/  TagMaxNum; scalar_t__ scan_devices; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN_TAG_QUEUEING ; 
 int TAG_QUEUEING_ ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dc390_slave_configure(struct scsi_device *sdev)
{
	struct dc390_acb *acb = (struct dc390_acb *)sdev->host->hostdata;
	struct dc390_dcb *dcb = (struct dc390_dcb *)sdev->hostdata;

	acb->scan_devices = 0;
	if (sdev->tagged_supported && (dcb->DevMode & TAG_QUEUEING_)) {
		dcb->SyncMode |= EN_TAG_QUEUEING;
		scsi_activate_tcq(sdev, acb->TagMaxNum);
	}

	return 0;
}