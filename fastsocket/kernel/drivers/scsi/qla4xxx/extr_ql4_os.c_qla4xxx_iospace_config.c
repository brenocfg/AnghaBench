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
struct scsi_qla_host {unsigned long pio_address; unsigned long pio_length; int /*<<< orphan*/  reg; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned long MIN_IOBASE_LEN ; 
 int /*<<< orphan*/  ioremap (unsigned long,unsigned long) ; 
 scalar_t__ pci_request_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_flags (int /*<<< orphan*/ ,int) ; 
 unsigned long pci_resource_len (int /*<<< orphan*/ ,int) ; 
 unsigned long pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 

int qla4xxx_iospace_config(struct scsi_qla_host *ha)
{
	unsigned long pio, pio_len, pio_flags;
	unsigned long mmio, mmio_len, mmio_flags;

	pio = pci_resource_start(ha->pdev, 0);
	pio_len = pci_resource_len(ha->pdev, 0);
	pio_flags = pci_resource_flags(ha->pdev, 0);
	if (pio_flags & IORESOURCE_IO) {
		if (pio_len < MIN_IOBASE_LEN) {
			ql4_printk(KERN_WARNING, ha,
				"Invalid PCI I/O region size\n");
			pio = 0;
		}
	} else {
		ql4_printk(KERN_WARNING, ha, "region #0 not a PIO resource\n");
		pio = 0;
	}

	/* Use MMIO operations for all accesses. */
	mmio = pci_resource_start(ha->pdev, 1);
	mmio_len = pci_resource_len(ha->pdev, 1);
	mmio_flags = pci_resource_flags(ha->pdev, 1);

	if (!(mmio_flags & IORESOURCE_MEM)) {
		ql4_printk(KERN_ERR, ha,
		    "region #0 not an MMIO resource, aborting\n");

		goto iospace_error_exit;
	}

	if (mmio_len < MIN_IOBASE_LEN) {
		ql4_printk(KERN_ERR, ha,
		    "Invalid PCI mem region size, aborting\n");
		goto iospace_error_exit;
	}

	if (pci_request_regions(ha->pdev, DRIVER_NAME)) {
		ql4_printk(KERN_WARNING, ha,
		    "Failed to reserve PIO/MMIO regions\n");

		goto iospace_error_exit;
	}

	ha->pio_address = pio;
	ha->pio_length = pio_len;
	ha->reg = ioremap(mmio, MIN_IOBASE_LEN);
	if (!ha->reg) {
		ql4_printk(KERN_ERR, ha,
		    "cannot remap MMIO, aborting\n");

		goto iospace_error_exit;
	}

	return 0;

iospace_error_exit:
	return -ENOMEM;
}