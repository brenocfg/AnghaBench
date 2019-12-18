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
struct TYPE_5__ {int* pen_pos; int page; } ;

/* Variables and functions */
 unsigned int PEV_PICO_PNEXT ; 
 unsigned int PEV_PICO_PPREV ; 
 unsigned int PEV_PICO_SWINP ; 
 int PICO_PEN_ADJUST_X ; 
 int PICO_PEN_ADJUST_Y ; 
 TYPE_3__ Pico ; 
 int* PicoPad ; 
 TYPE_2__ PicoPicohw ; 
 int /*<<< orphan*/  emu_status_msg (char*,...) ; 
 int pico_inp_mode ; 
 int pico_pen_x ; 
 int pico_pen_y ; 

void run_events_pico(unsigned int events)
{
	int lim_x;

	if (events & PEV_PICO_SWINP) {
		pico_inp_mode++;
		if (pico_inp_mode > 2)
			pico_inp_mode = 0;
		switch (pico_inp_mode) {
			case 2: emu_status_msg("Input: Pen on Pad"); break;
			case 1: emu_status_msg("Input: Pen on Storyware"); break;
			case 0: emu_status_msg("Input: Joystick");
				PicoPicohw.pen_pos[0] = PicoPicohw.pen_pos[1] = 0x8000;
				break;
		}
	}
	if (events & PEV_PICO_PPREV) {
		PicoPicohw.page--;
		if (PicoPicohw.page < 0)
			PicoPicohw.page = 0;
		emu_status_msg("Page %i", PicoPicohw.page);
	}
	if (events & PEV_PICO_PNEXT) {
		PicoPicohw.page++;
		if (PicoPicohw.page > 6)
			PicoPicohw.page = 6;
		emu_status_msg("Page %i", PicoPicohw.page);
	}

	if (pico_inp_mode == 0)
		return;

	/* handle other input modes */
	if (PicoPad[0] & 1) pico_pen_y--;
	if (PicoPad[0] & 2) pico_pen_y++;
	if (PicoPad[0] & 4) pico_pen_x--;
	if (PicoPad[0] & 8) pico_pen_x++;
	PicoPad[0] &= ~0x0f; // release UDLR

	lim_x = (Pico.video.reg[12]&1) ? 319 : 255;
	if (pico_pen_y < 8)
		pico_pen_y = 8;
	if (pico_pen_y > 224 - PICO_PEN_ADJUST_Y)
		pico_pen_y = 224 - PICO_PEN_ADJUST_Y;
	if (pico_pen_x < 0)
		pico_pen_x = 0;
	if (pico_pen_x > lim_x - PICO_PEN_ADJUST_X)
		pico_pen_x = lim_x - PICO_PEN_ADJUST_X;

	PicoPicohw.pen_pos[0] = pico_pen_x;
	if (!(Pico.video.reg[12] & 1))
		PicoPicohw.pen_pos[0] += pico_pen_x / 4;
	PicoPicohw.pen_pos[0] += 0x3c;
	PicoPicohw.pen_pos[1] = pico_inp_mode == 1 ? (0x2f8 + pico_pen_y) : (0x1fc + pico_pen_y);
}