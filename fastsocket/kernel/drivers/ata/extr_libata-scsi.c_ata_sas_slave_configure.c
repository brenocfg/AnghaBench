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
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_scsi_dev_config (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_sdev_config (struct scsi_device*) ; 

int ata_sas_slave_configure(struct scsi_device *sdev, struct ata_port *ap)
{
	ata_scsi_sdev_config(sdev);
	ata_scsi_dev_config(sdev, ap->link.device);
	return 0;
}