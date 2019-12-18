#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
#define  XFER_MW_DMA_0 138 
#define  XFER_MW_DMA_1 137 
#define  XFER_MW_DMA_2 136 
#define  XFER_PIO_0 135 
#define  XFER_PIO_1 134 
#define  XFER_PIO_2 133 
#define  XFER_PIO_3 132 
#define  XFER_PIO_4 131 
#define  XFER_SW_DMA_0 130 
#define  XFER_SW_DMA_1 129 
#define  XFER_SW_DMA_2 128 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void triflex_set_mode(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	u32 triflex_timings = 0;
	u16 timing = 0;
	u8 channel_offset = hwif->channel ? 0x74 : 0x70, unit = drive->dn & 1;

	pci_read_config_dword(dev, channel_offset, &triflex_timings);

	switch(speed) {
		case XFER_MW_DMA_2:
			timing = 0x0103; 
			break;
		case XFER_MW_DMA_1:
			timing = 0x0203;
			break;
		case XFER_MW_DMA_0:
			timing = 0x0808;
			break;
		case XFER_SW_DMA_2:
		case XFER_SW_DMA_1:
		case XFER_SW_DMA_0:
			timing = 0x0f0f;
			break;
		case XFER_PIO_4:
			timing = 0x0202;
			break;
		case XFER_PIO_3:
			timing = 0x0204;
			break;
		case XFER_PIO_2:
			timing = 0x0404;
			break;
		case XFER_PIO_1:
			timing = 0x0508;
			break;
		case XFER_PIO_0:
			timing = 0x0808;
			break;
	}

	triflex_timings &= ~(0xFFFF << (16 * unit));
	triflex_timings |= (timing << (16 * unit));
	
	pci_write_config_dword(dev, channel_offset, triflex_timings);
}