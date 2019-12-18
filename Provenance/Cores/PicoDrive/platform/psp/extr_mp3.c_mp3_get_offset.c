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
struct TYPE_3__ {int Status_CDC; } ;
struct TYPE_4__ {int* s68k_regs; TYPE_1__ scd; } ;

/* Variables and functions */
 int PAHW_MCD ; 
 int PicoAHW ; 
 int PicoOpt ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  lprintf (char*,unsigned int,int,int) ; 
 scalar_t__ mp3_handle ; 
 int mp3_src_pos ; 
 int mp3_src_size ; 

int mp3_get_offset(void) // 0-1023
{
	unsigned int offs1024 = 0;
	int cdda_on;

	cdda_on = (PicoAHW & PAHW_MCD) && (PicoOpt&0x800) && !(Pico_mcd->s68k_regs[0x36] & 1) &&
			(Pico_mcd->scd.Status_CDC & 1) && mp3_handle >= 0;

	if (cdda_on) {
		offs1024  = mp3_src_pos << 7;
		offs1024 /= mp3_src_size >> 3;
	}
	lprintf("offs1024=%u (%i/%i)\n", offs1024, mp3_src_pos, mp3_src_size);

	return offs1024;
}