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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 unsigned char* ioremap (int,int) ; 
 int /*<<< orphan*/  iounmap (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 

bool viafb_lcd_get_mobile_state(bool *mobile)
{
	unsigned char *romptr, *tableptr;
	u8 core_base;
	unsigned char *biosptr;
	/* Rom address */
	u32 romaddr = 0x000C0000;
	u16 start_pattern = 0;

	biosptr = ioremap(romaddr, 0x10000);

	memcpy(&start_pattern, biosptr, 2);
	/* Compare pattern */
	if (start_pattern == 0xAA55) {
		/* Get the start of Table */
		/* 0x1B means BIOS offset position */
		romptr = biosptr + 0x1B;
		tableptr = biosptr + *((u16 *) romptr);

		/* Get the start of biosver structure */
		/* 18 means BIOS version position. */
		romptr = tableptr + 18;
		romptr = biosptr + *((u16 *) romptr);

		/* The offset should be 44, but the
		   actual image is less three char. */
		/* pRom += 44; */
		romptr += 41;

		core_base = *romptr++;

		if (core_base & 0x8)
			*mobile = false;
		else
			*mobile = true;
		/* release memory */
		iounmap(biosptr);

		return true;
	} else {
		iounmap(biosptr);
		return false;
	}
}