#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_7__* dot; } ;
struct TYPE_17__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_22__ {TYPE_8__ ir; TYPE_4__ accel; int /*<<< orphan*/  btns; } ;
struct TYPE_19__ {TYPE_5__* dot; } ;
struct TYPE_16__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
struct wiimote_t {int* event_buf; int btns; TYPE_9__ lstate; TYPE_6__ ir; TYPE_3__ accel; TYPE_2__ exp; int /*<<< orphan*/  battery_level; } ;
struct _wpad_thresh {int /*<<< orphan*/  ir; int /*<<< orphan*/  acc; int /*<<< orphan*/  btns; } ;
typedef  scalar_t__ s32 ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int btns_h; int /*<<< orphan*/  err; scalar_t__ data_present; TYPE_6__ ir; TYPE_3__ accel; TYPE_1__ exp; int /*<<< orphan*/  battery_level; } ;
typedef  TYPE_10__ WPADData ;
struct TYPE_20__ {int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; int /*<<< orphan*/  visible; } ;
struct TYPE_18__ {int visible; int /*<<< orphan*/  ry; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_CHECK_SIMPLE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_CONNECTED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
#define  WM_RPT_BTN 134 
#define  WM_RPT_BTN_ACC 133 
#define  WM_RPT_BTN_ACC_EXP 132 
#define  WM_RPT_BTN_ACC_IR 131 
#define  WM_RPT_BTN_ACC_IR_EXP 130 
#define  WM_RPT_BTN_EXP 129 
#define  WM_RPT_BTN_IR_EXP 128 
 scalar_t__ WPAD_DATA_ACCEL ; 
 scalar_t__ WPAD_DATA_BUTTONS ; 
 scalar_t__ WPAD_DATA_EXPANSION ; 
 scalar_t__ WPAD_DATA_IR ; 
 int /*<<< orphan*/  WPAD_ERR_NONE ; 
 int /*<<< orphan*/  WPAD_ERR_NOT_READY ; 
 int /*<<< orphan*/  WPAD_ERR_NO_CONTROLLER ; 
 int /*<<< orphan*/  WPAD_ERR_TRANSFER ; 
 int WPAD_MAX_IR_DOTS ; 
 int /*<<< orphan*/  __save_state (struct wiimote_t*) ; 
 int __wpad_read_expansion (struct wiimote_t*,TYPE_10__*,struct _wpad_thresh*) ; 

__attribute__((used)) static void __wpad_read_wiimote(struct wiimote_t *wm, WPADData *data, s32 *idle_time, struct _wpad_thresh *thresh)
{
	int i;
	int state_changed = 0;
	data->err = WPAD_ERR_TRANSFER;
	data->data_present = 0;
	data->battery_level = wm->battery_level;
	data->exp.type = wm->exp.type;
	if(wm && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_CONNECTED)) {
		if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_HANDSHAKE_COMPLETE)) {
			switch(wm->event_buf[0]) {
				case WM_RPT_BTN:
				case WM_RPT_BTN_ACC:
				case WM_RPT_BTN_ACC_IR:
				case WM_RPT_BTN_EXP:
				case WM_RPT_BTN_ACC_EXP:
				case WM_RPT_BTN_IR_EXP:
				case WM_RPT_BTN_ACC_IR_EXP:
					data->btns_h = (wm->btns&0xffff);
					data->data_present |= WPAD_DATA_BUTTONS;
					STATE_CHECK_SIMPLE(thresh->btns, wm->btns, wm->lstate.btns);
			}
			switch(wm->event_buf[0]) {
				case WM_RPT_BTN_ACC:
				case WM_RPT_BTN_ACC_IR:
				case WM_RPT_BTN_ACC_EXP:
				case WM_RPT_BTN_ACC_IR_EXP:
					data->accel = wm->accel;
					data->data_present |= WPAD_DATA_ACCEL;
					STATE_CHECK(thresh->acc, wm->accel.x, wm->lstate.accel.x);
					STATE_CHECK(thresh->acc, wm->accel.y, wm->lstate.accel.y);
					STATE_CHECK(thresh->acc, wm->accel.z, wm->lstate.accel.z);
			}
			switch(wm->event_buf[0]) {
				//IR requires acceleration
				//case WM_RPT_BTN_IR_EXP:
				case WM_RPT_BTN_ACC_IR:
				case WM_RPT_BTN_ACC_IR_EXP:
					data->ir = wm->ir;
					data->data_present |= WPAD_DATA_IR;
					for(i=0; i<WPAD_MAX_IR_DOTS; i++) {
						STATE_CHECK_SIMPLE(thresh->ir, wm->ir.dot[i].visible, wm->lstate.ir.dot[i].visible);
						STATE_CHECK(thresh->ir, wm->ir.dot[i].rx, wm->lstate.ir.dot[i].rx);
						STATE_CHECK(thresh->ir, wm->ir.dot[i].ry, wm->lstate.ir.dot[i].ry);
					}
			}
			switch(wm->event_buf[0]) {
				case WM_RPT_BTN_EXP:
				case WM_RPT_BTN_ACC_EXP:
				case WM_RPT_BTN_IR_EXP:
				case WM_RPT_BTN_ACC_IR_EXP:
					state_changed |= __wpad_read_expansion(wm,data,thresh);
					data->data_present |= WPAD_DATA_EXPANSION;
			}
			data->err = WPAD_ERR_NONE;
			if(state_changed) {
				*idle_time = 0;
				__save_state(wm);
			}
		} else
			data->err = WPAD_ERR_NOT_READY;
	} else
		data->err = WPAD_ERR_NO_CONTROLLER;
}