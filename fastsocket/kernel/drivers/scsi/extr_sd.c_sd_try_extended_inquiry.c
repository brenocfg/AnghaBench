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
struct scsi_device {scalar_t__ scsi_level; } ;

/* Variables and functions */
 scalar_t__ SCSI_SPC_2 ; 

__attribute__((used)) static int sd_try_extended_inquiry(struct scsi_device *sdp)
{
	/*
	 * Although VPD inquiries can go to SCSI-2 type devices,
	 * some USB ones crash on receiving them, and the pages
	 * we currently ask for are for SPC-3 and beyond
	 */
	if (sdp->scsi_level > SCSI_SPC_2)
		return 1;
	return 0;
}