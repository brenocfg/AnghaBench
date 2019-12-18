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
struct scsi_info_t {struct Scsi_Host* host; } ;
struct pcmcia_device {struct scsi_info_t* priv; } ;
struct Scsi_Host {scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void
SYM53C500_release(struct pcmcia_device *link)
{
	struct scsi_info_t *info = link->priv;
	struct Scsi_Host *shost = info->host;

	DEBUG(0, "SYM53C500_release(0x%p)\n", link);

	/*
	*  Do this before releasing/freeing resources.
	*/
	scsi_remove_host(shost);

	/*
	*  Interrupts getting hosed on card removal.  Try
	*  the following code, mostly from qlogicfas.c.
	*/
	if (shost->irq)
		free_irq(shost->irq, shost);
	if (shost->io_port && shost->n_io_port)
		release_region(shost->io_port, shost->n_io_port);

	pcmcia_disable_device(link);

	scsi_host_put(shost);
}