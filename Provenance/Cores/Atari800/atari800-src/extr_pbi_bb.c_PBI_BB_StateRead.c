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

/* Variables and functions */
 int BB_RAM_SIZE ; 
 scalar_t__ PBI_BB_enabled ; 
 int /*<<< orphan*/  StateSav_ReadFNAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StateSav_ReadINT (scalar_t__*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bb_PCR ; 
 int /*<<< orphan*/ * bb_ram ; 
 scalar_t__ bb_ram_bank_offset ; 
 int /*<<< orphan*/  bb_rom_bank ; 
 int /*<<< orphan*/  bb_rom_filename ; 
 scalar_t__ bb_rom_high_bit ; 
 int /*<<< orphan*/  bb_scsi_disk_filename ; 
 int /*<<< orphan*/  init_bb () ; 

void PBI_BB_StateRead(void)
{
	StateSav_ReadINT(&PBI_BB_enabled, 1);
	if (PBI_BB_enabled) {
		StateSav_ReadFNAME(bb_scsi_disk_filename);
		StateSav_ReadFNAME(bb_rom_filename);
		init_bb();
		StateSav_ReadINT(&bb_ram_bank_offset, 1);
		StateSav_ReadUBYTE(bb_ram, BB_RAM_SIZE);
		StateSav_ReadUBYTE(&bb_rom_bank, 1);
		StateSav_ReadINT(&bb_rom_high_bit, 1);
		StateSav_ReadUBYTE(&bb_PCR, 1);
	}
}