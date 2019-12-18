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
struct TYPE_4__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {int /*<<< orphan*/  dev; TYPE_1__ core; } ;
struct TYPE_5__ {struct ata_port* ap; int /*<<< orphan*/  ata_host; } ;
struct domain_device {TYPE_2__ sata_dev; TYPE_3__* port; } ;
struct ata_port {struct Scsi_Host* scsi_host; int /*<<< orphan*/  cbl; struct domain_device* private_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_SATA ; 
 int ENODEV ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*) ; 
 int /*<<< orphan*/  ata_host_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ata_port* ata_sas_port_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Scsi_Host*) ; 
 int /*<<< orphan*/  ata_sas_port_destroy (struct ata_port*) ; 
 int ata_sas_port_init (struct ata_port*) ; 
 int /*<<< orphan*/  sas_sata_ops ; 
 int /*<<< orphan*/  sata_port_info ; 

int sas_ata_init(struct domain_device *found_dev)
{
	struct sas_ha_struct *ha = found_dev->port->ha;
	struct Scsi_Host *shost = ha->core.shost;
	struct ata_port *ap;
	int rc;

	ata_host_init(&found_dev->sata_dev.ata_host, ha->dev, &sas_sata_ops);
	ap = ata_sas_port_alloc(&found_dev->sata_dev.ata_host,
				&sata_port_info,
				shost);
	if (!ap) {
		SAS_DPRINTK("ata_sas_port_alloc failed.\n");
		return -ENODEV;
	}

	ap->private_data = found_dev;
	ap->cbl = ATA_CBL_SATA;
	ap->scsi_host = shost;
	rc = ata_sas_port_init(ap);
	if (rc) {
		ata_sas_port_destroy(ap);
		return rc;
	}
	found_dev->sata_dev.ap = ap;

	return 0;
}