#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_device {scalar_t__ tagged_supported; struct Scsi_Host* host; } ;
struct Scsi_Host {int can_queue; scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  adpt_hba ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adpt_slave_configure(struct scsi_device * device)
{
	struct Scsi_Host *host = device->host;
	adpt_hba* pHba;

	pHba = (adpt_hba *) host->hostdata[0];

	if (host->can_queue && device->tagged_supported) {
		scsi_adjust_queue_depth(device, MSG_SIMPLE_TAG,
				host->can_queue - 1);
	} else {
		scsi_adjust_queue_depth(device, 0, 1);
	}
	return 0;
}