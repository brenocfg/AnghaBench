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
struct TYPE_2__ {int pos; int* offset; int /*<<< orphan*/  aspect; } ;
struct wiimote_t {TYPE_1__ ir; } ;
typedef  enum ir_position_t { ____Placeholder_ir_position_t } ir_position_t ;

/* Variables and functions */
 int /*<<< orphan*/  WIIUSE_ASPECT_16_9 ; 
 int /*<<< orphan*/  WIIUSE_ASPECT_4_3 ; 
#define  WIIUSE_IR_ABOVE 129 
#define  WIIUSE_IR_BELOW 128 
 int WM_ASPECT_16_9_Y ; 
 int WM_ASPECT_4_3_Y ; 

void wiiuse_set_ir_position(struct wiimote_t* wm, enum ir_position_t pos) {
	if (!wm)	return;

	wm->ir.pos = pos;

	switch (pos) {

		case WIIUSE_IR_ABOVE:
			wm->ir.offset[0] = 0;

			if (wm->ir.aspect == WIIUSE_ASPECT_16_9)
				wm->ir.offset[1] = WM_ASPECT_16_9_Y/2 - 70;
			else if (wm->ir.aspect == WIIUSE_ASPECT_4_3)
				wm->ir.offset[1] = WM_ASPECT_4_3_Y/2 - 100;

			return;

		case WIIUSE_IR_BELOW:
			wm->ir.offset[0] = 0;

			if (wm->ir.aspect == WIIUSE_ASPECT_16_9)
				wm->ir.offset[1] = -WM_ASPECT_16_9_Y/2 + 70;
			else if (wm->ir.aspect == WIIUSE_ASPECT_4_3)
				wm->ir.offset[1] = -WM_ASPECT_4_3_Y/2 + 100;

			return;

		default:
			return;
	};
}