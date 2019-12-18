#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ATA_100 ; 
 size_t ATA_133 ; 
 size_t const XFER_UDMA_0 ; 
 int** cvs_time_value ; 
 int** cycle_time_value ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,size_t,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,size_t,int) ; 
 size_t sis_ata133_get_base (TYPE_2__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_ata133_program_udma_timings(ide_drive_t *drive, const u8 mode)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u32 regdw = 0;
	u8 drive_pci = sis_ata133_get_base(drive), clk, idx;

	pci_read_config_dword(dev, drive_pci, &regdw);

	regdw |= 0x04;
	regdw &= 0xfffff00f;
	/* check if ATA133 enable */
	clk = (regdw & 0x08) ? ATA_133 : ATA_100;
	idx = mode - XFER_UDMA_0;
	regdw |= cycle_time_value[clk][idx] << 4;
	regdw |= cvs_time_value[clk][idx] << 8;

	pci_write_config_dword(dev, drive_pci, regdw);
}