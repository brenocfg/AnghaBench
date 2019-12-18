#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* bram; } ;
struct TYPE_3__ {void* data; } ;

/* Variables and functions */
 int PAHW_MCD ; 
 int PicoAHW ; 
 TYPE_2__* Pico_mcd ; 
 unsigned int RETRO_MEMORY_SAVE_RAM ; 
 TYPE_1__ SRam ; 

void *retro_get_memory_data(unsigned id)
{
	if (id != RETRO_MEMORY_SAVE_RAM)
		return NULL;

	if (PicoAHW & PAHW_MCD)
		return Pico_mcd->bram;
	else
		return SRam.data;
}