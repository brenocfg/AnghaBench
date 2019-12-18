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
 int ANTIC_margin ; 
 int /*<<< orphan*/ * ANTIC_xe_ptr ; 
 int /*<<< orphan*/  MEMORY_CopyFromMem (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MEMORY_dCopyFromMem (int,int /*<<< orphan*/ *,int) ; 
 void* MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * antic_memory ; 
 int* chars_read ; 
 size_t md ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int screenaddr ; 

__attribute__((used)) static void antic_load(void)
{
#ifdef PAGED_MEM
	UBYTE *antic_memptr = antic_memory + ANTIC_margin;
	UWORD new_screenaddr = screenaddr + chars_read[md];
	if ((screenaddr ^ new_screenaddr) & 0xf000) {
		do
			*antic_memptr++ = MEMORY_dGetByte(screenaddr++);
		while (screenaddr & 0xfff);
		screenaddr -= 0x1000;
		new_screenaddr -= 0x1000;
	}
	while (screenaddr < new_screenaddr)
		*antic_memptr++ = MEMORY_dGetByte(screenaddr++);
#else
	UWORD new_screenaddr = screenaddr + chars_read[md];
	if ((screenaddr ^ new_screenaddr) & 0xf000) {
		int bytes = (-screenaddr) & 0xfff;
		if (ANTIC_xe_ptr != NULL && screenaddr < 0x8000 && screenaddr >= 0x4000) {
			memcpy(antic_memory + ANTIC_margin, ANTIC_xe_ptr + (screenaddr - 0x4000), bytes);
			if (new_screenaddr & 0xfff)
				memcpy(antic_memory + ANTIC_margin + bytes, ANTIC_xe_ptr + (screenaddr + bytes - 0x5000), new_screenaddr & 0xfff);
		}
		else if ((screenaddr & 0xf000) == 0xd000) {
			MEMORY_CopyFromMem(screenaddr, antic_memory + ANTIC_margin, bytes);
			if (new_screenaddr & 0xfff)
				MEMORY_CopyFromMem((UWORD) (screenaddr + bytes - 0x1000), antic_memory + ANTIC_margin + bytes, new_screenaddr & 0xfff);
		}
		else {
			MEMORY_dCopyFromMem(screenaddr, antic_memory + ANTIC_margin, bytes);
			if (new_screenaddr & 0xfff)
				MEMORY_dCopyFromMem(screenaddr + bytes - 0x1000, antic_memory + ANTIC_margin + bytes, new_screenaddr & 0xfff);
		}
		screenaddr = new_screenaddr - 0x1000;
	}
	else {
		if (ANTIC_xe_ptr != NULL && screenaddr < 0x8000 && screenaddr >= 0x4000)
			memcpy(antic_memory + ANTIC_margin, ANTIC_xe_ptr + (screenaddr - 0x4000), chars_read[md]);
		else if ((screenaddr & 0xf000) == 0xd000)
			MEMORY_CopyFromMem(screenaddr, antic_memory + ANTIC_margin, chars_read[md]);
		else
			MEMORY_dCopyFromMem(screenaddr, antic_memory + ANTIC_margin, chars_read[md]);
		screenaddr = new_screenaddr;
	}
#endif
}