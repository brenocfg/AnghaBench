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
typedef  int ubyte ;
struct TYPE_3__ {int x; int y; } ;
struct TYPE_4__ {TYPE_1__ pos; } ;
struct classic_ctrl_t {int type; int ls_raw; int btns; int rs_raw; float r_shoulder; float l_shoulder; TYPE_2__ rjs; TYPE_2__ ljs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIG_ENDIAN_SHORT (short) ; 
 int CLASSIC_CTRL_BUTTON_FULL_L ; 
 int CLASSIC_CTRL_BUTTON_FULL_R ; 
 int /*<<< orphan*/  calc_joystick_state (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  classic_ctrl_pressed_buttons (struct classic_ctrl_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ l ; 
 scalar_t__ r ; 

void classic_ctrl_event(struct classic_ctrl_t* cc, ubyte* msg) {
	//int i;

	/* decrypt data */
	/*
	for (i = 0; i < 6; ++i)
		msg[i] = (msg[i] ^ 0x17) + 0x17;
	*/
	if (cc->type==2) {
		classic_ctrl_pressed_buttons(cc, BIG_ENDIAN_SHORT(*(short*)(msg + 8)));

		/* 12-bit little endian values adjusted to 8-bit */
		cc->ljs.pos.x = (msg[0] >> 4) | (msg[1] << 4);
		cc->rjs.pos.x = (msg[2] >> 4) | (msg[3] << 4);
		cc->ljs.pos.y = (msg[4] >> 4) | (msg[5] << 4);
		cc->rjs.pos.y = (msg[6] >> 4) | (msg[7] << 4);

		cc->ls_raw = cc->btns & CLASSIC_CTRL_BUTTON_FULL_L ? 0x1F : 0;
		cc->rs_raw = cc->btns & CLASSIC_CTRL_BUTTON_FULL_R ? 0x1F : 0;
	}
	else {
		classic_ctrl_pressed_buttons(cc, BIG_ENDIAN_SHORT(*(short*)(msg + 4)));

		/* left/right buttons */
		cc->ls_raw = (((msg[2] & 0x60) >> 2) | ((msg[3] & 0xE0) >> 5));
		cc->rs_raw = (msg[3] & 0x1F);

		/*
		 *	TODO - LR range hardcoded from 0x00 to 0x1F.
		 *	This is probably in the calibration somewhere.
		 */
#ifndef GEKKO
		cc->r_shoulder = ((float)r / 0x1F);
		cc->l_shoulder = ((float)l / 0x1F);
#endif
		/* calculate joystick orientation */
		cc->ljs.pos.x = (msg[0] & 0x3F);
		cc->ljs.pos.y = (msg[1] & 0x3F);
		cc->rjs.pos.x = ((msg[0] & 0xC0) >> 3) | ((msg[1] & 0xC0) >> 5) | ((msg[2] & 0x80) >> 7);
		cc->rjs.pos.y = (msg[2] & 0x1F);
	}

#ifndef GEKKO
	calc_joystick_state(&cc->ljs, cc->ljs.pos.x, cc->ljs.pos.y);
	calc_joystick_state(&cc->rjs, cc->rjs.pos.x, cc->rjs.pos.y);
#endif
}