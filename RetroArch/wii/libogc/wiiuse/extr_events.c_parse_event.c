#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ubyte ;
struct TYPE_3__ {int x; int y; int z; } ;
struct wiimote_t {int* event_buf; int /*<<< orphan*/  event; int /*<<< orphan*/  gforce; TYPE_1__ accel; int /*<<< orphan*/  accel_calib; int /*<<< orphan*/  orient; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIMOTE_IS_FLAG_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIUSE_EVENT ; 
 int /*<<< orphan*/  WIIUSE_SMOOTHING ; 
 int /*<<< orphan*/  WIIUSE_WARNING (char*,int) ; 
#define  WM_RPT_ACK 137 
#define  WM_RPT_BTN 136 
#define  WM_RPT_BTN_ACC 135 
#define  WM_RPT_BTN_ACC_EXP 134 
#define  WM_RPT_BTN_ACC_IR 133 
#define  WM_RPT_BTN_ACC_IR_EXP 132 
#define  WM_RPT_BTN_EXP 131 
#define  WM_RPT_BTN_IR_EXP 130 
#define  WM_RPT_CTRL_STATUS 129 
#define  WM_RPT_READ 128 
 int /*<<< orphan*/  calculate_basic_ir (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  calculate_extended_ir (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  calculate_gforce (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calculate_orientation (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_ack (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  event_data_read (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  event_status (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  handle_expansion (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  wiiuse_pressed_buttons (struct wiimote_t*,int*) ; 

void parse_event(struct wiimote_t *wm)
{
	ubyte event;
	ubyte *msg;

	event = wm->event_buf[0];
	msg = wm->event_buf+1;
	//printf("parse_event(%02x,%p)\n",event,msg);
	switch(event) {
		case WM_RPT_CTRL_STATUS:
			event_status(wm,msg);
			return;
		case WM_RPT_READ:
			event_data_read(wm,msg);
			return;
		case WM_RPT_ACK:
			event_ack(wm,msg);
			return;
		case WM_RPT_BTN:
			wiiuse_pressed_buttons(wm,msg);
			break;
		case WM_RPT_BTN_ACC:
			wiiuse_pressed_buttons(wm,msg);

			wm->accel.x = (msg[2]<<2)|((msg[0]>>5)&3);
			wm->accel.y = (msg[3]<<2)|((msg[1]>>4)&2);
			wm->accel.z = (msg[4]<<2)|((msg[1]>>5)&2);
#ifndef GEKKO
			/* calculate the remote orientation */
			calculate_orientation(&wm->accel_calib, &wm->accel, &wm->orient, WIIMOTE_IS_FLAG_SET(wm, WIIUSE_SMOOTHING));

			/* calculate the gforces on each axis */
			calculate_gforce(&wm->accel_calib, &wm->accel, &wm->gforce);
#endif
			break;
		case WM_RPT_BTN_ACC_IR:
			wiiuse_pressed_buttons(wm,msg);

			wm->accel.x = (msg[2]<<2)|((msg[0]>>5)&3);
			wm->accel.y = (msg[3]<<2)|((msg[1]>>4)&2);
			wm->accel.z = (msg[4]<<2)|((msg[1]>>5)&2);
#ifndef GEKKO
			/* calculate the remote orientation */
			calculate_orientation(&wm->accel_calib, &wm->accel, &wm->orient, WIIMOTE_IS_FLAG_SET(wm, WIIUSE_SMOOTHING));

			/* calculate the gforces on each axis */
			calculate_gforce(&wm->accel_calib, &wm->accel, &wm->gforce);
#endif
			calculate_extended_ir(wm, msg+5);
			break;
		case WM_RPT_BTN_EXP:
			wiiuse_pressed_buttons(wm,msg);
			handle_expansion(wm,msg+2);
			break;
		case WM_RPT_BTN_ACC_EXP:
			/* button - motion - expansion */
			wiiuse_pressed_buttons(wm, msg);

			wm->accel.x = (msg[2]<<2)|((msg[0]>>5)&3);
			wm->accel.y = (msg[3]<<2)|((msg[1]>>4)&2);
			wm->accel.z = (msg[4]<<2)|((msg[1]>>5)&2);
#ifndef GEKKO
			calculate_orientation(&wm->accel_calib, &wm->accel, &wm->orient, WIIMOTE_IS_FLAG_SET(wm, WIIUSE_SMOOTHING));
			calculate_gforce(&wm->accel_calib, &wm->accel, &wm->gforce);
#endif
			handle_expansion(wm, msg+5);
			break;
		case WM_RPT_BTN_IR_EXP:
			wiiuse_pressed_buttons(wm,msg);
			calculate_basic_ir(wm, msg+2);
			handle_expansion(wm,msg+12);
			break;
		case WM_RPT_BTN_ACC_IR_EXP:
			/* button - motion - ir - expansion */
			wiiuse_pressed_buttons(wm, msg);

			wm->accel.x = (msg[2]<<2)|((msg[0]>>5)&3);
			wm->accel.y = (msg[3]<<2)|((msg[1]>>4)&2);
			wm->accel.z = (msg[4]<<2)|((msg[1]>>5)&2);
#ifndef GEKKO
			calculate_orientation(&wm->accel_calib, &wm->accel, &wm->orient, WIIMOTE_IS_FLAG_SET(wm, WIIUSE_SMOOTHING));
			calculate_gforce(&wm->accel_calib, &wm->accel, &wm->gforce);
#endif
			/* ir */
			calculate_basic_ir(wm, msg+5);

			handle_expansion(wm, msg+15);
			break;
		default:
			WIIUSE_WARNING("Unknown event, can not handle it [Code 0x%x].", event);
			return;
	}

	/* was there an event? */
	wm->event = WIIUSE_EVENT;
}