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
 int PBI_MIO_enabled ; 
 int /*<<< orphan*/  StateSav_ReadFNAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_mio () ; 
 int /*<<< orphan*/ * mio_ram ; 
 int mio_ram_bank_offset ; 
 int mio_ram_enabled ; 
 int mio_ram_size ; 
 int /*<<< orphan*/  mio_rom_bank ; 
 int /*<<< orphan*/  mio_rom_filename ; 
 int /*<<< orphan*/  mio_scsi_disk_filename ; 

void PBI_MIO_StateRead(void)
{
	StateSav_ReadINT(&PBI_MIO_enabled, 1);
	if (PBI_MIO_enabled) {
		StateSav_ReadFNAME(mio_scsi_disk_filename);
		StateSav_ReadFNAME(mio_rom_filename);
		StateSav_ReadINT(&mio_ram_size, 1);
		init_mio();
		StateSav_ReadINT(&mio_ram_bank_offset, 1);
		StateSav_ReadUBYTE(mio_ram, mio_ram_size);
		StateSav_ReadUBYTE(&mio_rom_bank, 1);
		StateSav_ReadINT(&mio_ram_enabled, 1);
	}
}