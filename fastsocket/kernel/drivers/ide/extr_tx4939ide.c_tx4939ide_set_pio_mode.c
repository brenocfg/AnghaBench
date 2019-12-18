#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {int select_data; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_get_best_pio_mode (TYPE_2__*,int,int) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx4939ide_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	ide_hwif_t *hwif = drive->hwif;
	int is_slave = drive->dn;
	u32 mask, val;
	u8 safe = pio;
	ide_drive_t *pair;

	pair = ide_get_pair_dev(drive);
	if (pair)
		safe = min(safe, ide_get_best_pio_mode(pair, 255, 4));
	/*
	 * Update Command Transfer Mode for master/slave and Data
	 * Transfer Mode for this drive.
	 */
	mask = is_slave ? 0x07f00000 : 0x000007f0;
	val = ((safe << 8) | (pio << 4)) << (is_slave ? 16 : 0);
	hwif->select_data = (hwif->select_data & ~mask) | val;
	/* tx4939ide_tf_load_fixup() will set the Sys_Ctl register */
}