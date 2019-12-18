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
struct scsi_device {scalar_t__ tagged_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_lun_queue_depth ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bfad_im_slave_configure(struct scsi_device *sdev)
{
	if (sdev->tagged_supported)
		scsi_activate_tcq(sdev, bfa_lun_queue_depth);
	else
		scsi_deactivate_tcq(sdev, bfa_lun_queue_depth);

	return 0;
}