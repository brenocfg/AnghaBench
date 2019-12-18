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
struct pci_dev {int dummy; } ;
struct ide_timing {int /*<<< orphan*/  udma; int /*<<< orphan*/  recover; int /*<<< orphan*/  active; int /*<<< orphan*/  rec8b; int /*<<< orphan*/  act8b; int /*<<< orphan*/  setup; } ;

/* Variables and functions */
 int AMD_8BIT_TIMING ; 
 int AMD_ADDRESS_SETUP ; 
 int AMD_DRIVE_TIMING ; 
 int AMD_UDMA_TIMING ; 
#define  ATA_UDMA2 131 
#define  ATA_UDMA4 130 
#define  ATA_UDMA5 129 
#define  ATA_UDMA6 128 
 int* amd_cyc2udma ; 
 int amd_offset (struct pci_dev*) ; 
 size_t clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void amd_set_speed(struct pci_dev *dev, u8 dn, u8 udma_mask,
			  struct ide_timing *timing)
{
	u8 t = 0, offset = amd_offset(dev);

	pci_read_config_byte(dev, AMD_ADDRESS_SETUP + offset, &t);
	t = (t & ~(3 << ((3 - dn) << 1))) | ((clamp_val(timing->setup, 1, 4) - 1) << ((3 - dn) << 1));
	pci_write_config_byte(dev, AMD_ADDRESS_SETUP + offset, t);

	pci_write_config_byte(dev, AMD_8BIT_TIMING + offset + (1 - (dn >> 1)),
		((clamp_val(timing->act8b, 1, 16) - 1) << 4) | (clamp_val(timing->rec8b, 1, 16) - 1));

	pci_write_config_byte(dev, AMD_DRIVE_TIMING + offset + (3 - dn),
		((clamp_val(timing->active, 1, 16) - 1) << 4) | (clamp_val(timing->recover, 1, 16) - 1));

	switch (udma_mask) {
	case ATA_UDMA2: t = timing->udma ? (0xc0 | (clamp_val(timing->udma, 2, 5) - 2)) : 0x03; break;
	case ATA_UDMA4: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 2, 10)]) : 0x03; break;
	case ATA_UDMA5: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 1, 10)]) : 0x03; break;
	case ATA_UDMA6: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 1, 15)]) : 0x03; break;
	default: return;
	}

	pci_write_config_byte(dev, AMD_UDMA_TIMING + offset + (3 - dn), t);
}