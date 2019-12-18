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
struct scsi_device {int no_uld_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int scsi_device_reprobe (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,char*) ; 

__attribute__((used)) static void
_scsih_reprobe_lun(struct scsi_device *sdev, void *no_uld_attach)
{
	int rc;
	sdev->no_uld_attach = no_uld_attach ? 1 : 0;
	sdev_printk(KERN_INFO, sdev, "%s raid component\n",
	    sdev->no_uld_attach ? "hidding" : "exposing");
	rc = scsi_device_reprobe(sdev);
}