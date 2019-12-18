#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ubyte ;
struct TYPE_12__ {int x; int y; int z; } ;
struct TYPE_11__ {int x; int y; } ;
struct TYPE_10__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {TYPE_4__ pos; TYPE_3__ max; TYPE_2__ min; TYPE_1__ center; } ;
struct nunchuk_t {int /*<<< orphan*/  gforce; TYPE_5__ accel; int /*<<< orphan*/  accel_calib; int /*<<< orphan*/  orient; TYPE_7__ js; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUNCHUK_IS_FLAG_SET (struct nunchuk_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIUSE_SMOOTHING ; 
 int /*<<< orphan*/  calc_joystick_state (TYPE_7__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  calculate_gforce (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calculate_orientation (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nunchuk_pressed_buttons (struct nunchuk_t*,int) ; 

void nunchuk_event(struct nunchuk_t* nc, ubyte* msg) {
	//int i;

	/* decrypt data */
	/*
	for (i = 0; i < 6; ++i)
		msg[i] = (msg[i] ^ 0x17) + 0x17;
	*/
	/* get button states */
	nunchuk_pressed_buttons(nc, msg[5]);

	nc->js.pos.x = msg[0];
	nc->js.pos.y = msg[1];

	/* extend min and max values to physical range of motion */
	if (nc->js.center.x) {
		if (nc->js.min.x > nc->js.pos.x) nc->js.min.x = nc->js.pos.x;
		if (nc->js.max.x < nc->js.pos.x) nc->js.max.x = nc->js.pos.x;
	}
	if (nc->js.center.y) {
		if (nc->js.min.y > nc->js.pos.y) nc->js.min.y = nc->js.pos.y;
		if (nc->js.max.y < nc->js.pos.y) nc->js.max.y = nc->js.pos.y;
	}

#ifndef GEKKO
	/* calculate joystick state */
	calc_joystick_state(&nc->js, nc->js.pos.x, nc->js.pos.y);
#endif
	/* calculate orientation */
	nc->accel.x = (msg[2]<<2) + ((msg[5]>>2)&3);
	nc->accel.y = (msg[3]<<2) + ((msg[5]>>4)&3);
	nc->accel.z = (msg[4]<<2) + ((msg[5]>>6)&3);
#ifndef GEKKO
	calculate_orientation(&nc->accel_calib, &nc->accel, &nc->orient, NUNCHUK_IS_FLAG_SET(nc, WIIUSE_SMOOTHING));
	calculate_gforce(&nc->accel_calib, &nc->accel, &nc->gforce);
#endif
}