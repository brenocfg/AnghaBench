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
struct TYPE_4__ {int* reg; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_5__ {int* pen_pos; } ;

/* Variables and functions */
 unsigned int PBTN_DOWN ; 
 unsigned int PBTN_LEFT ; 
 unsigned int PBTN_RIGHT ; 
 unsigned int PBTN_UP ; 
 int PICO_PEN_ADJUST_X ; 
 int PICO_PEN_ADJUST_Y ; 
 TYPE_3__ Pico ; 
 int* PicoPad ; 
 TYPE_2__ PicoPicohw ; 
 int /*<<< orphan*/  emu_RunEventsPico (unsigned int) ; 
 int pico_inp_mode ; 
 int pico_pen_x ; 
 int pico_pen_y ; 

__attribute__((used)) static void RunEventsPico(unsigned int events, unsigned int keys)
{
	emu_RunEventsPico(events);

	if (pico_inp_mode != 0)
	{
		PicoPad[0] &= ~0x0f; // release UDLR
		if (keys & PBTN_UP)   { pico_pen_y--; if (pico_pen_y < 8) pico_pen_y = 8; }
		if (keys & PBTN_DOWN) { pico_pen_y++; if (pico_pen_y > 224-PICO_PEN_ADJUST_Y) pico_pen_y = 224-PICO_PEN_ADJUST_Y; }
		if (keys & PBTN_LEFT) { pico_pen_x--; if (pico_pen_x < 0) pico_pen_x = 0; }
		if (keys & PBTN_RIGHT) {
			int lim = (Pico.video.reg[12]&1) ? 319 : 255;
			pico_pen_x++;
			if (pico_pen_x > lim-PICO_PEN_ADJUST_X)
				pico_pen_x = lim-PICO_PEN_ADJUST_X;
		}
		PicoPicohw.pen_pos[0] = pico_pen_x;
		if (!(Pico.video.reg[12]&1)) PicoPicohw.pen_pos[0] += pico_pen_x/4;
		PicoPicohw.pen_pos[0] += 0x3c;
		PicoPicohw.pen_pos[1] = pico_inp_mode == 1 ? (0x2f8 + pico_pen_y) : (0x1fc + pico_pen_y);
	}
}