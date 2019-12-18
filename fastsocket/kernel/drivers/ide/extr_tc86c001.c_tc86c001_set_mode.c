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
typedef  int u16 ;
struct TYPE_4__ {int config_data; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {scalar_t__ dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
#define  XFER_MW_DMA_0 140 
#define  XFER_MW_DMA_1 139 
#define  XFER_MW_DMA_2 138 
#define  XFER_PIO_0 137 
#define  XFER_PIO_1 136 
#define  XFER_PIO_2 135 
#define  XFER_PIO_3 134 
#define  XFER_PIO_4 133 
#define  XFER_UDMA_0 132 
#define  XFER_UDMA_1 131 
#define  XFER_UDMA_2 130 
#define  XFER_UDMA_3 129 
#define  XFER_UDMA_4 128 
 int inw (unsigned long) ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 

__attribute__((used)) static void tc86c001_set_mode(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif	= drive->hwif;
	unsigned long scr_port	= hwif->config_data + (drive->dn ? 0x02 : 0x00);
	u16 mode, scr		= inw(scr_port);

	switch (speed) {
	case XFER_UDMA_4:	mode = 0x00c0; break;
	case XFER_UDMA_3:	mode = 0x00b0; break;
	case XFER_UDMA_2:	mode = 0x00a0; break;
	case XFER_UDMA_1:	mode = 0x0090; break;
	case XFER_UDMA_0:	mode = 0x0080; break;
	case XFER_MW_DMA_2:	mode = 0x0070; break;
	case XFER_MW_DMA_1:	mode = 0x0060; break;
	case XFER_MW_DMA_0:	mode = 0x0050; break;
	case XFER_PIO_4:	mode = 0x0400; break;
	case XFER_PIO_3:	mode = 0x0300; break;
	case XFER_PIO_2:	mode = 0x0200; break;
	case XFER_PIO_1:	mode = 0x0100; break;
	case XFER_PIO_0:
	default:		mode = 0x0000; break;
	}

	scr &= (speed < XFER_MW_DMA_0) ? 0xf8ff : 0xff0f;
	scr |= mode;
	outw(scr, scr_port);
}