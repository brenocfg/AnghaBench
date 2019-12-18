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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int /*<<< orphan*/  id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {int port_flags; } ;

/* Variables and functions */
 int IDE_PFLAG_PROBING ; 
 int ata_id_pio_need_iordy (int /*<<< orphan*/ ,scalar_t__ const) ; 

int ide_pio_need_iordy(ide_drive_t *drive, const u8 pio)
{
	/*
	 * IORDY may lead to controller lock up on certain controllers
	 * if the port is not occupied.
	 */
	if (pio == 0 && (drive->hwif->port_flags & IDE_PFLAG_PROBING))
		return 0;
	return ata_id_pio_need_iordy(drive->id, pio);
}