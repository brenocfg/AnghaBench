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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BASE ; 
 int ENODEV ; 
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_SI ; 
 int /*<<< orphan*/  SIS5595_ENABLE_REG ; 
 int SIS5595_EXTENT ; 
 int SMB_INDEX ; 
 int acpi_check_region (int,int,int /*<<< orphan*/ ) ; 
 int* blacklist ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int force_addr ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 int sis5595_base ; 
 TYPE_1__ sis5595_driver ; 

__attribute__((used)) static int sis5595_setup(struct pci_dev *SIS5595_dev)
{
	u16 a;
	u8 val;
	int *i;
	int retval = -ENODEV;

	/* Look for imposters */
	for (i = blacklist; *i != 0; i++) {
		struct pci_dev *dev;
		dev = pci_get_device(PCI_VENDOR_ID_SI, *i, NULL);
		if (dev) {
			dev_err(&SIS5595_dev->dev, "Looked for SIS5595 but found unsupported device %.4x\n", *i);
			pci_dev_put(dev);
			return -ENODEV;
		}
	}

	/* Determine the address of the SMBus areas */
	pci_read_config_word(SIS5595_dev, ACPI_BASE, &sis5595_base);
	if (sis5595_base == 0 && force_addr == 0) {
		dev_err(&SIS5595_dev->dev, "ACPI base address uninitialized - upgrade BIOS or use force_addr=0xaddr\n");
		return -ENODEV;
	}

	if (force_addr)
		sis5595_base = force_addr & ~(SIS5595_EXTENT - 1);
	dev_dbg(&SIS5595_dev->dev, "ACPI Base address: %04x\n", sis5595_base);

	/* NB: We grab just the two SMBus registers here, but this may still
	 * interfere with ACPI :-(  */
	retval = acpi_check_region(sis5595_base + SMB_INDEX, 2,
				   sis5595_driver.name);
	if (retval)
		return retval;

	if (!request_region(sis5595_base + SMB_INDEX, 2,
			    sis5595_driver.name)) {
		dev_err(&SIS5595_dev->dev, "SMBus registers 0x%04x-0x%04x already in use!\n",
			sis5595_base + SMB_INDEX, sis5595_base + SMB_INDEX + 1);
		return -ENODEV;
	}

	if (force_addr) {
		dev_info(&SIS5595_dev->dev, "forcing ISA address 0x%04X\n", sis5595_base);
		if (pci_write_config_word(SIS5595_dev, ACPI_BASE, sis5595_base)
		    != PCIBIOS_SUCCESSFUL)
			goto error;
		if (pci_read_config_word(SIS5595_dev, ACPI_BASE, &a)
		    != PCIBIOS_SUCCESSFUL)
			goto error;
		if ((a & ~(SIS5595_EXTENT - 1)) != sis5595_base) {
			/* doesn't work for some chips! */
			dev_err(&SIS5595_dev->dev, "force address failed - not supported?\n");
			goto error;
		}
	}

	if (pci_read_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, &val)
	    != PCIBIOS_SUCCESSFUL)
		goto error;
	if ((val & 0x80) == 0) {
		dev_info(&SIS5595_dev->dev, "enabling ACPI\n");
		if (pci_write_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, val | 0x80)
		    != PCIBIOS_SUCCESSFUL)
			goto error;
		if (pci_read_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, &val)
		    != PCIBIOS_SUCCESSFUL)
			goto error;
		if ((val & 0x80) == 0) {
			/* doesn't work for some chips? */
			dev_err(&SIS5595_dev->dev, "ACPI enable failed - not supported?\n");
			goto error;
		}
	}

	/* Everything is happy */
	return 0;

error:
	release_region(sis5595_base + SMB_INDEX, 2);
	return retval;
}