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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {scalar_t__ pio_mask; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 scalar_t__ XFER_PIO_4 ; 
 int fls (scalar_t__) ; 
 scalar_t__ ide_find_dma_mode (TYPE_2__*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u8 ide_rate_filter(ide_drive_t *drive, u8 speed)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 mode = ide_find_dma_mode(drive, speed);

	if (mode == 0) {
		if (hwif->pio_mask)
			mode = fls(hwif->pio_mask) - 1 + XFER_PIO_0;
		else
			mode = XFER_PIO_4;
	}

/*	printk("%s: mode 0x%02x, speed 0x%02x\n", __func__, mode, speed); */

	return min(speed, mode);
}