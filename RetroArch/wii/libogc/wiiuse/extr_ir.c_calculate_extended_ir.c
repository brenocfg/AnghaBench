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
struct ir_dot_t {int rx; int ry; int size; int visible; } ;

/* Variables and functions */
 void* BIG_ENDIAN_SHORT (int) ; 
 int /*<<< orphan*/  WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_ACC ; 
 int /*<<< orphan*/  interpret_ir_data (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void calculate_extended_ir(struct wiimote_t* wm, ubyte* data) {
	struct ir_dot_t* dot = wm->ir.dot;
	int i;

	for (i = 0; i < 4; ++i) {
		dot[i].rx = 1023 - (data[3*i] | ((data[(3*i)+2] & 0x30) << 4));
		dot[i].ry = data[(3*i)+1] | ((data[(3*i)+2] & 0xC0) << 2);

		dot[i].size = data[(3*i)+2];

		dot[i].rx = BIG_ENDIAN_SHORT(dot[i].rx);
		dot[i].ry = BIG_ENDIAN_SHORT(dot[i].ry);

		dot[i].size = dot[i].size&0x0f;

		/* if in range set to visible */
		if (dot[i].ry == 1023)
			dot[i].visible = 0;
		else
			dot[i].visible = 1;
	}
#ifndef GEKKO
	interpret_ir_data(&wm->ir,&wm->orient,WIIMOTE_IS_SET(wm, WIIMOTE_STATE_ACC));
#endif
}