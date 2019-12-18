#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
typedef  int port_type ;
struct TYPE_3__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
#define  PORT_PATA0 130 
#define  PORT_PATA1 129 
#define  PORT_SATA 128 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 jmicron_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *pdev = to_pci_dev(hwif->dev);

	u32 control;
	u32 control5;

	int port = hwif->channel;
	port_type port_map[2];

	pci_read_config_dword(pdev, 0x40, &control);

	/* There are two basic mappings. One has the two SATA ports merged
	   as master/slave and the secondary as PATA, the other has only the
	   SATA port mapped */
	if (control & (1 << 23)) {
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_PATA0;
	} else {
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_SATA;
	}

	/* The 365/366 may have this bit set to map the second PATA port
	   as the internal primary channel */
	pci_read_config_dword(pdev, 0x80, &control5);
	if (control5 & (1<<24))
		port_map[0] = PORT_PATA1;

	/* The two ports may then be logically swapped by the firmware */
	if (control & (1 << 22))
		port = port ^ 1;

	/*
	 *	Now we know which physical port we are talking about we can
	 *	actually do our cable checking etc. Thankfully we don't need
	 *	to do the plumbing for other cases.
	 */
	switch (port_map[port]) {
	case PORT_PATA0:
		if (control & (1 << 3))	/* 40/80 pin primary */
			return ATA_CBL_PATA40;
		return ATA_CBL_PATA80;
	case PORT_PATA1:
		if (control5 & (1 << 19))	/* 40/80 pin secondary */
			return ATA_CBL_PATA40;
		return ATA_CBL_PATA80;
	case PORT_SATA:
		break;
	}
	/* Avoid bogus "control reaches end of non-void function" */
	return ATA_CBL_PATA80;
}