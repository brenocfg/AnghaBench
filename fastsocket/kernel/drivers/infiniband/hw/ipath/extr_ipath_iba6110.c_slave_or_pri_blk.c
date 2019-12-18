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
typedef  int u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ipath_devdata {int ipath_ht_slave_off; int ipath_lbus_width; int ipath_lbus_speed; int /*<<< orphan*/  ipath_lbus_info; int /*<<< orphan*/  ipath_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPATH_8BIT_IN_HT0 ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ipath_dbg (char*,...) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,...) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int,int*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int,int*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void slave_or_pri_blk(struct ipath_devdata *dd, struct pci_dev *pdev,
			     int pos, u8 cap_type)
{
	u8 linkwidth = 0, linkerr, link_a_b_off, link_off;
	u16 linkctrl = 0;
	int i;

	dd->ipath_ht_slave_off = pos;
	/* command word, master_host bit */
	/* master host || slave */
	if ((cap_type >> 2) & 1)
		link_a_b_off = 4;
	else
		link_a_b_off = 0;
	ipath_cdbg(VERBOSE, "HT%u (Link %c) connected to processor\n",
		   link_a_b_off ? 1 : 0,
		   link_a_b_off ? 'B' : 'A');

	link_a_b_off += pos;

	/*
	 * check both link control registers; clear both HT CRC sets if
	 * necessary.
	 */
	for (i = 0; i < 2; i++) {
		link_off = pos + i * 4 + 0x4;
		if (pci_read_config_word(pdev, link_off, &linkctrl))
			ipath_dev_err(dd, "Couldn't read HT link control%d "
				      "register\n", i);
		else if (linkctrl & (0xf << 8)) {
			ipath_cdbg(VERBOSE, "Clear linkctrl%d CRC Error "
				   "bits %x\n", i, linkctrl & (0xf << 8));
			/*
			 * now write them back to clear the error.
			 */
			pci_write_config_word(pdev, link_off,
					      linkctrl & (0xf << 8));
		}
	}

	/*
	 * As with HT CRC bits, same for protocol errors that might occur
	 * during boot.
	 */
	for (i = 0; i < 2; i++) {
		link_off = pos + i * 4 + 0xd;
		if (pci_read_config_byte(pdev, link_off, &linkerr))
			dev_info(&pdev->dev, "Couldn't read linkerror%d "
				 "of HT slave/primary block\n", i);
		else if (linkerr & 0xf0) {
			ipath_cdbg(VERBOSE, "HT linkerr%d bits 0x%x set, "
				   "clearing\n", linkerr >> 4, i);
			/*
			 * writing the linkerr bits that are set will clear
			 * them
			 */
			if (pci_write_config_byte
			    (pdev, link_off, linkerr))
				ipath_dbg("Failed write to clear HT "
					  "linkerror%d\n", i);
			if (pci_read_config_byte(pdev, link_off, &linkerr))
				dev_info(&pdev->dev, "Couldn't reread "
					 "linkerror%d of HT slave/primary "
					 "block\n", i);
			else if (linkerr & 0xf0)
				dev_info(&pdev->dev, "HT linkerror%d bits "
					 "0x%x couldn't be cleared\n",
					 i, linkerr >> 4);
		}
	}

	/*
	 * this is just for our link to the host, not devices connected
	 * through tunnel.
	 */

	if (pci_read_config_byte(pdev, link_a_b_off + 7, &linkwidth))
		ipath_dev_err(dd, "Couldn't read HT link width "
			      "config register\n");
	else {
		u32 width;
		switch (linkwidth & 7) {
		case 5:
			width = 4;
			break;
		case 4:
			width = 2;
			break;
		case 3:
			width = 32;
			break;
		case 1:
			width = 16;
			break;
		case 0:
		default:	/* if wrong, assume 8 bit */
			width = 8;
			break;
		}

		dd->ipath_lbus_width = width;

		if (linkwidth != 0x11) {
			ipath_dev_err(dd, "Not configured for 16 bit HT "
				      "(%x)\n", linkwidth);
			if (!(linkwidth & 0xf)) {
				ipath_dbg("Will ignore HT lane1 errors\n");
				dd->ipath_flags |= IPATH_8BIT_IN_HT0;
			}
		}
	}

	/*
	 * this is just for our link to the host, not devices connected
	 * through tunnel.
	 */
	if (pci_read_config_byte(pdev, link_a_b_off + 0xd, &linkwidth))
		ipath_dev_err(dd, "Couldn't read HT link frequency "
			      "config register\n");
	else {
		u32 speed;
		switch (linkwidth & 0xf) {
		case 6:
			speed = 1000;
			break;
		case 5:
			speed = 800;
			break;
		case 4:
			speed = 600;
			break;
		case 3:
			speed = 500;
			break;
		case 2:
			speed = 400;
			break;
		case 1:
			speed = 300;
			break;
		default:
			/*
			 * assume reserved and vendor-specific are 200...
			 */
		case 0:
			speed = 200;
			break;
		}
		dd->ipath_lbus_speed = speed;
	}

	snprintf(dd->ipath_lbus_info, sizeof(dd->ipath_lbus_info),
		"HyperTransport,%uMHz,x%u\n",
		dd->ipath_lbus_speed,
		dd->ipath_lbus_width);
}