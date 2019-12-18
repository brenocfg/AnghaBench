#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ frame_count; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {size_t size; int* data; } ;

/* Variables and functions */
 int PAHW_MCD ; 
 TYPE_3__ Pico ; 
 int PicoAHW ; 
 unsigned int RETRO_MEMORY_SAVE_RAM ; 
 TYPE_2__ SRam ; 

size_t retro_get_memory_size(unsigned id)
{
	unsigned int i;
	int sum;

	if (id != RETRO_MEMORY_SAVE_RAM)
		return 0;

	if (PicoAHW & PAHW_MCD)
		// bram
		return 0x2000;

	if (Pico.m.frame_count == 0)
		return SRam.size;

	// if game doesn't write to sram, don't report it to
	// libretro so that RA doesn't write out zeroed .srm
    for (i = 0, sum = 0; i < SRam.size; i++) {
		sum |= SRam.data[i];
    }

	return (sum != 0) ? SRam.size : 0;
}