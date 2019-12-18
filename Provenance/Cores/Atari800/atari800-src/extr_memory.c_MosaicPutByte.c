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
typedef  int UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Log_print (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_SetRAM (int,int) ; 
 int /*<<< orphan*/  MEMORY_SetROM (int,int) ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 scalar_t__ MEMORY_mem ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int mosaic_curbank ; 
 int mosaic_current_num_banks ; 
 scalar_t__ mosaic_ram ; 

__attribute__((used)) static void MosaicPutByte(UWORD addr, UBYTE byte)
{
	int newbank;
	if (addr < 0xffc0) return;
#ifdef DEBUG
	Log_print("MosaicPutByte:%4X:%2X",addr,byte);
#endif
	newbank = addr - 0xffc0;
	if (newbank == mosaic_curbank || (newbank >= mosaic_current_num_banks && mosaic_curbank >= mosaic_current_num_banks)) return; /*same bank or rom -> rom*/
	if (newbank >= mosaic_current_num_banks && mosaic_curbank < mosaic_current_num_banks) {
		/*ram ->rom*/
		memcpy(mosaic_ram + mosaic_curbank*0x1000, MEMORY_mem + 0xc000,0x1000);
		MEMORY_dFillMem(0xc000, 0xff, 0x1000);
		MEMORY_SetROM(0xc000, 0xcfff);
	}
	else if (newbank < mosaic_current_num_banks && mosaic_curbank >= mosaic_current_num_banks) {
		/*rom->ram*/
		memcpy(MEMORY_mem + 0xc000, mosaic_ram+newbank*0x1000,0x1000);
		MEMORY_SetRAM(0xc000, 0xcfff);
	}
	else {
		/*ram -> ram*/
		memcpy(mosaic_ram + mosaic_curbank*0x1000, MEMORY_mem + 0xc000, 0x1000);
		memcpy(MEMORY_mem + 0xc000, mosaic_ram + newbank*0x1000, 0x1000);
		MEMORY_SetRAM(0xc000, 0xcfff);
	}
	mosaic_curbank = newbank;
}