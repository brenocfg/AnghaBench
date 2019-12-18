#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ubyte ;
struct TYPE_2__ {struct ir_dot_t* dot; } ;
struct wiimote_t {int /*<<< orphan*/  orient; TYPE_1__ ir; } ;
struct ir_dot_t {int rx; int ry; int visible; scalar_t__ size; } ;

/* Variables and functions */
 void* BIG_ENDIAN_SHORT (int) ; 
 int /*<<< orphan*/  WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_ACC ; 
 int /*<<< orphan*/  interpret_ir_data (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void calculate_basic_ir(struct wiimote_t* wm, ubyte* data) {
	struct ir_dot_t* dot = wm->ir.dot;
	int i;

	dot[0].rx = 1023 - (data[0] | ((data[2] & 0x30) << 4));
	dot[0].ry = data[1] | ((data[2] & 0xC0) << 2);

	dot[1].rx = 1023 - (data[3] | ((data[2] & 0x03) << 8));
	dot[1].ry = data[4] | ((data[2] & 0x0C) << 6);

	dot[2].rx = 1023 - (data[5] | ((data[7] & 0x30) << 4));
	dot[2].ry = data[6] | ((data[7] & 0xC0) << 2);

	dot[3].rx = 1023 - (data[8] | ((data[7] & 0x03) << 8));
	dot[3].ry = data[9] | ((data[7] & 0x0C) << 6);

	/* set each IR spot to visible if spot is in range */
	for (i = 0; i < 4; ++i) {
		dot[i].rx = BIG_ENDIAN_SHORT(dot[i].rx);
		dot[i].ry = BIG_ENDIAN_SHORT(dot[i].ry);

		if (dot[i].ry == 1023)
			dot[i].visible = 0;
		else {
			dot[i].visible = 1;
			dot[i].size = 0;		/* since we don't know the size, set it as 0 */
		}
	}
#ifndef GEKKO
	interpret_ir_data(&wm->ir,&wm->orient,WIIMOTE_IS_SET(wm, WIIMOTE_STATE_ACC));
#endif
}