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
struct scsi_device {scalar_t__ channel; TYPE_2__* hostdata; struct Scsi_Host* host; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {TYPE_1__* vtarget; } ;
typedef  TYPE_2__ VirtDevice ;
struct TYPE_7__ {int /*<<< orphan*/ * ioc; } ;
struct TYPE_5__ {scalar_t__ deleted; } ;
typedef  TYPE_3__ MPT_SCSI_HOST ;
typedef  int /*<<< orphan*/  MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ MPTSAS_RAID_CHANNEL ; 
 int /*<<< orphan*/  mptsas_add_device_component_starget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptsas_add_device_component_starget_ir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mptscsih_slave_configure (struct scsi_device*) ; 
 int /*<<< orphan*/  sas_read_port_mode_page (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 TYPE_3__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
mptsas_slave_configure(struct scsi_device *sdev)
{
	struct Scsi_Host	*host = sdev->host;
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER	*ioc = hd->ioc;
	VirtDevice	*vdevice = sdev->hostdata;

	if (vdevice->vtarget->deleted) {
		sdev_printk(KERN_INFO, sdev, "clearing deleted flag\n");
		vdevice->vtarget->deleted = 0;
	}

	/*
	 * RAID volumes placed beyond the last expected port.
	 * Ignore sending sas mode pages in that case..
	 */
	if (sdev->channel == MPTSAS_RAID_CHANNEL) {
		mptsas_add_device_component_starget_ir(ioc, scsi_target(sdev));
		goto out;
	}

	sas_read_port_mode_page(sdev);

	mptsas_add_device_component_starget(ioc, scsi_target(sdev));

 out:
	return mptscsih_slave_configure(sdev);
}