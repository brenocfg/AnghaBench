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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 int inw (unsigned long) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 tc86c001_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	unsigned long sc_base = pci_resource_start(dev, 5);
	u16 scr1 = inw(sc_base + 0x00);

	/*
	 * System Control  1 Register bit 13 (PDIAGN):
	 * 0=80-pin cable, 1=40-pin cable
	 */
	return (scr1 & 0x2000) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
}