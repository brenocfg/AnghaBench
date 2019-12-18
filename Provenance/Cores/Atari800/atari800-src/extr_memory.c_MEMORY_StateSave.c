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
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * ANTIC_xe_ptr ; 
 scalar_t__ Atari800_MACHINE_800 ; 
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_machine_type ; 
 scalar_t__ MEMORY_HARDWARE ; 
 scalar_t__ MEMORY_RAM ; 
 int MEMORY_RAM_320_COMPY_SHOP ; 
 int MEMORY_RAM_320_RAMBO ; 
 scalar_t__ MEMORY_ROM ; 
 int /*<<< orphan*/ * MEMORY_ROM_PutByte ; 
 scalar_t__* MEMORY_attrib ; 
 int MEMORY_axlon_0f_mirror ; 
 int MEMORY_axlon_num_banks ; 
 scalar_t__* MEMORY_basic ; 
 int MEMORY_cartA0BF_enabled ; 
 int MEMORY_enable_mapram ; 
 scalar_t__* MEMORY_mem ; 
 scalar_t__* MEMORY_os ; 
 int MEMORY_ram_size ; 
 scalar_t__ MEMORY_selftest_enabled ; 
 int /*<<< orphan*/ ** MEMORY_writemap ; 
 scalar_t__* MEMORY_xegame ; 
 scalar_t__ PIA_PORTB ; 
 scalar_t__ PIA_PORTB_mask ; 
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (scalar_t__*,int) ; 
 scalar_t__* antic_bank_under_selftest ; 
 scalar_t__* atarixe_memory ; 
 int atarixe_memory_size ; 
 int axlon_curbank ; 
 scalar_t__* axlon_ram ; 
 scalar_t__* mapram_memory ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,int) ; 
 int mosaic_curbank ; 
 int mosaic_current_num_banks ; 
 scalar_t__* mosaic_ram ; 
 scalar_t__* under_atarixl_os ; 
 scalar_t__* under_cartA0BF ; 

void MEMORY_StateSave(UBYTE SaveVerbose)
{
	int temp;
	UBYTE byte;

	/* Axlon/Mosaic for 400/800 */
	if (Atari800_machine_type == Atari800_MACHINE_800) {
		StateSav_SaveINT(&MEMORY_axlon_num_banks, 1);
		if (MEMORY_axlon_num_banks > 0){
			StateSav_SaveINT(&axlon_curbank, 1);
			StateSav_SaveINT(&MEMORY_axlon_0f_mirror, 1);
			StateSav_SaveUBYTE(axlon_ram, MEMORY_axlon_num_banks * 0x4000);
		}
		StateSav_SaveINT(&mosaic_current_num_banks, 1);
		if (mosaic_current_num_banks > 0) {
			StateSav_SaveINT(&mosaic_curbank, 1);
			StateSav_SaveUBYTE(mosaic_ram, mosaic_current_num_banks * 0x1000);
		}
	}

	/* Save amount of base RAM in kilobytes. */
	temp = MEMORY_ram_size > 64 ? 64 : MEMORY_ram_size;
	StateSav_SaveINT(&temp, 1);
	StateSav_SaveUBYTE(&MEMORY_mem[0], 65536);
#ifndef PAGED_ATTRIB
	StateSav_SaveUBYTE(&MEMORY_attrib[0], 65536);
#else
	{
		/* I assume here that consecutive calls to StateSav_SaveUBYTE()
		   are equivalent to a single call with all the values
		   (i.e. StateSav_SaveUBYTE() doesn't write any headers). */
		UBYTE attrib_page[256];
		int i;
		for (i = 0; i < 256; i++) {
			if (MEMORY_writemap[i] == NULL)
				memset(attrib_page, MEMORY_RAM, 256);
			else if (MEMORY_writemap[i] == MEMORY_ROM_PutByte)
				memset(attrib_page, MEMORY_ROM, 256);
			else if (i == 0x4f || i == 0x5f || i == 0x8f || i == 0x9f) {
				/* special case: Bounty Bob bank switching registers */
				memset(attrib_page, MEMORY_ROM, 256);
				attrib_page[0xf6] = MEMORY_HARDWARE;
				attrib_page[0xf7] = MEMORY_HARDWARE;
				attrib_page[0xf8] = MEMORY_HARDWARE;
				attrib_page[0xf9] = MEMORY_HARDWARE;
			}
			else {
				memset(attrib_page, MEMORY_HARDWARE, 256);
			}
			StateSav_SaveUBYTE(&attrib_page[0], 256);
		}
	}
#endif

	if (Atari800_machine_type == Atari800_MACHINE_XLXE) {
		if (SaveVerbose != 0)
			StateSav_SaveUBYTE(&MEMORY_basic[0], 8192);
		StateSav_SaveUBYTE(&under_cartA0BF[0], 8192);

		if (SaveVerbose != 0)
			StateSav_SaveUBYTE(&MEMORY_os[0], 16384);
		StateSav_SaveUBYTE(&under_atarixl_os[0], 16384);
		if (SaveVerbose != 0)
			StateSav_SaveUBYTE(MEMORY_xegame, 0x2000);
	}

	/* Save amount of XE RAM in 16KB banks. */
	temp = (MEMORY_ram_size - 64) / 16;
	if (temp < 0)
		temp = 0;
	StateSav_SaveINT(&temp, 1);
	if (MEMORY_ram_size == MEMORY_RAM_320_RAMBO || MEMORY_ram_size == MEMORY_RAM_320_COMPY_SHOP) {
		/* Save specific banking type. */
		temp = MEMORY_ram_size - 320;
		StateSav_SaveINT(&temp, 1);
	}
	byte = PIA_PORTB | PIA_PORTB_mask;
	StateSav_SaveUBYTE(&byte, 1);

	StateSav_SaveINT(&MEMORY_cartA0BF_enabled, 1);

	if (MEMORY_ram_size > 64) {
		StateSav_SaveUBYTE(&atarixe_memory[0], atarixe_memory_size);
		if (ANTIC_xe_ptr != NULL && MEMORY_selftest_enabled)
			StateSav_SaveUBYTE(antic_bank_under_selftest, 0x800);
	}

	/* Simius XL/XE MapRAM expansion */
	if (Atari800_machine_type == Atari800_MACHINE_XLXE && MEMORY_ram_size > 20) {
		StateSav_SaveINT(&MEMORY_enable_mapram, 1);
		if (MEMORY_enable_mapram) {
			StateSav_SaveUBYTE( mapram_memory, 0x800 );
		}
	}
}