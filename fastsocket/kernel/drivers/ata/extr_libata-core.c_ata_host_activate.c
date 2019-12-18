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
struct scsi_host_template {int dummy; } ;
struct ata_host {int n_ports; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ports; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int ata_host_register (struct ata_host*,struct scsi_host_template*) ; 
 int ata_host_start (struct ata_host*) ; 
 int /*<<< orphan*/  ata_port_desc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int,struct ata_host*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct ata_host*) ; 

int ata_host_activate(struct ata_host *host, int irq,
		      irq_handler_t irq_handler, unsigned long irq_flags,
		      struct scsi_host_template *sht)
{
	int i, rc;

	rc = ata_host_start(host);
	if (rc)
		return rc;

	/* Special case for polling mode */
	if (!irq) {
		WARN_ON(irq_handler);
		return ata_host_register(host, sht);
	}

	rc = devm_request_irq(host->dev, irq, irq_handler, irq_flags,
			      dev_driver_string(host->dev), host);
	if (rc)
		return rc;

	for (i = 0; i < host->n_ports; i++)
		ata_port_desc(host->ports[i], "irq %d", irq);

	rc = ata_host_register(host, sht);
	/* if failed, just free the IRQ and leave ports alone */
	if (rc)
		devm_free_irq(host->dev, irq, host);

	return rc;
}