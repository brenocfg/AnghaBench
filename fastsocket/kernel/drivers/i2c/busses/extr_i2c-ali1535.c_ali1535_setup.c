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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned char ALI1535_SMBIO_EN ; 
 int ALI1535_SMB_IOSIZE ; 
 int ENODEV ; 
 int /*<<< orphan*/  SMBBA ; 
 int /*<<< orphan*/  SMBCFG ; 
 int /*<<< orphan*/  SMBCLK ; 
 int /*<<< orphan*/  SMBHSTCFG ; 
 int /*<<< orphan*/  SMBREV ; 
 int acpi_check_region (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ ali1535_driver ; 
 int ali1535_smba ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali1535_setup(struct pci_dev *dev)
{
	int retval = -ENODEV;
	unsigned char temp;

	/* Check the following things:
		- SMB I/O address is initialized
		- Device is enabled
		- We can use the addresses
	*/

	/* Determine the address of the SMBus area */
	pci_read_config_word(dev, SMBBA, &ali1535_smba);
	ali1535_smba &= (0xffff & ~(ALI1535_SMB_IOSIZE - 1));
	if (ali1535_smba == 0) {
		dev_warn(&dev->dev,
			"ALI1535_smb region uninitialized - upgrade BIOS?\n");
		goto exit;
	}

	retval = acpi_check_region(ali1535_smba, ALI1535_SMB_IOSIZE,
				   ali1535_driver.name);
	if (retval)
		goto exit;

	if (!request_region(ali1535_smba, ALI1535_SMB_IOSIZE,
			    ali1535_driver.name)) {
		dev_err(&dev->dev, "ALI1535_smb region 0x%x already in use!\n",
			ali1535_smba);
		goto exit;
	}

	/* check if whole device is enabled */
	pci_read_config_byte(dev, SMBCFG, &temp);
	if ((temp & ALI1535_SMBIO_EN) == 0) {
		dev_err(&dev->dev, "SMB device not enabled - upgrade BIOS?\n");
		goto exit_free;
	}

	/* Is SMB Host controller enabled? */
	pci_read_config_byte(dev, SMBHSTCFG, &temp);
	if ((temp & 1) == 0) {
		dev_err(&dev->dev, "SMBus controller not enabled - upgrade BIOS?\n");
		goto exit_free;
	}

	/* set SMB clock to 74KHz as recommended in data sheet */
	pci_write_config_byte(dev, SMBCLK, 0x20);

	/*
	  The interrupt routing for SMB is set up in register 0x77 in the
	  1533 ISA Bridge device, NOT in the 7101 device.
	  Don't bother with finding the 1533 device and reading the register.
	if ((....... & 0x0F) == 1)
		dev_dbg(&dev->dev, "ALI1535 using Interrupt 9 for SMBus.\n");
	*/
	pci_read_config_byte(dev, SMBREV, &temp);
	dev_dbg(&dev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&dev->dev, "ALI1535_smba = 0x%X\n", ali1535_smba);

	retval = 0;
exit:
	return retval;

exit_free:
	release_region(ali1535_smba, ALI1535_SMB_IOSIZE);
	return retval;
}