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
struct Scsi_Host {scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ PCI_bus ; 
 int /*<<< orphan*/  PCI_dev ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int fdomain_16x0_release(struct Scsi_Host *shpnt)
{
	if (shpnt->irq)
		free_irq(shpnt->irq, shpnt);
	if (shpnt->io_port && shpnt->n_io_port)
		release_region(shpnt->io_port, shpnt->n_io_port);
	if (PCI_bus)
		pci_dev_put(PCI_dev);
	return 0;
}