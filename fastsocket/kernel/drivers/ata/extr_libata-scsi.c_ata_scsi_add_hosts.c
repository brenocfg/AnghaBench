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
struct scsi_host_template {int dummy; } ;
struct ata_port {struct Scsi_Host* scsi_host; TYPE_1__* host; int /*<<< orphan*/  print_id; } ;
struct ata_host {int n_ports; struct ata_port** ports; } ;
struct Scsi_Host {int max_id; int max_lun; int max_channel; int max_cmd_len; int max_host_blocked; int /*<<< orphan*/  unique_id; int /*<<< orphan*/ * transportt; int /*<<< orphan*/ * hostdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ata_scsi_transport_template ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

int ata_scsi_add_hosts(struct ata_host *host, struct scsi_host_template *sht)
{
	int i, rc;

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		struct Scsi_Host *shost;

		rc = -ENOMEM;
		shost = scsi_host_alloc(sht, sizeof(struct ata_port *));
		if (!shost)
			goto err_alloc;

		*(struct ata_port **)&shost->hostdata[0] = ap;
		ap->scsi_host = shost;

		shost->transportt = &ata_scsi_transport_template;
		shost->unique_id = ap->print_id;
		shost->max_id = 16;
		shost->max_lun = 1;
		shost->max_channel = 1;
		shost->max_cmd_len = 16;

		/* Schedule policy is determined by ->qc_defer()
		 * callback and it needs to see every deferred qc.
		 * Set host_blocked to 1 to prevent SCSI midlayer from
		 * automatically deferring requests.
		 */
		shost->max_host_blocked = 1;

		rc = scsi_add_host(ap->scsi_host, ap->host->dev);
		if (rc)
			goto err_add;
	}

	return 0;

 err_add:
	scsi_host_put(host->ports[i]->scsi_host);
 err_alloc:
	while (--i >= 0) {
		struct Scsi_Host *shost = host->ports[i]->scsi_host;

		scsi_remove_host(shost);
		scsi_host_put(shost);
	}
	return rc;
}