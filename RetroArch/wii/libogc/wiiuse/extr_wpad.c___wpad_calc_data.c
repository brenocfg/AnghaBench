#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct accel_t {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_1__ pos; } ;
struct nunchuk_t {int btns; int /*<<< orphan*/  gforce; int /*<<< orphan*/  accel; struct accel_t accel_calib; int /*<<< orphan*/  orient; TYPE_5__ js; } ;
struct classic_ctrl_t {int r_shoulder; int l_shoulder; int btns; TYPE_5__ rjs; TYPE_5__ ljs; int /*<<< orphan*/  ls_raw; int /*<<< orphan*/  rs_raw; } ;
typedef  int f32 ;
struct TYPE_9__ {int type; struct classic_ctrl_t classic; struct nunchuk_t nunchuk; } ;
struct TYPE_11__ {int /*<<< orphan*/  glitch_cnt; int /*<<< orphan*/  error_cnt; int /*<<< orphan*/  angle; int /*<<< orphan*/  z; int /*<<< orphan*/  distance; int /*<<< orphan*/  ay; int /*<<< orphan*/  ax; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  sensorbar; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {scalar_t__ err; int data_present; int btns_h; TYPE_2__ exp; int /*<<< orphan*/  orient; TYPE_4__ ir; int /*<<< orphan*/  gforce; int /*<<< orphan*/  accel; } ;
typedef  TYPE_3__ WPADData ;

/* Variables and functions */
#define  EXP_CLASSIC 129 
#define  EXP_NUNCHUK 128 
 int WPAD_DATA_ACCEL ; 
 int WPAD_DATA_EXPANSION ; 
 int WPAD_DATA_IR ; 
 scalar_t__ WPAD_ERR_NONE ; 
 int /*<<< orphan*/  calc_joystick_state (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_gforce (struct accel_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calculate_orientation (struct accel_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interpret_ir_data (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __wpad_calc_data(WPADData *data,WPADData *lstate,struct accel_t *accel_calib,u32 smoothed)
{
	if(data->err!=WPAD_ERR_NONE) return;

	data->orient = lstate->orient;

	data->ir.state = lstate->ir.state;
	data->ir.sensorbar = lstate->ir.sensorbar;
	data->ir.x = lstate->ir.x;
	data->ir.y = lstate->ir.y;
	data->ir.sx = lstate->ir.sx;
	data->ir.sy = lstate->ir.sy;
	data->ir.ax = lstate->ir.ax;
	data->ir.ay = lstate->ir.ay;
	data->ir.distance = lstate->ir.distance;
	data->ir.z = lstate->ir.z;
	data->ir.angle = lstate->ir.angle;
	data->ir.error_cnt = lstate->ir.error_cnt;
	data->ir.glitch_cnt = lstate->ir.glitch_cnt;

	if(data->data_present & WPAD_DATA_ACCEL) {
		calculate_orientation(accel_calib, &data->accel, &data->orient, smoothed);
		calculate_gforce(accel_calib, &data->accel, &data->gforce);
	}
	if(data->data_present & WPAD_DATA_IR) {
		interpret_ir_data(&data->ir,&data->orient);
	}
	if(data->data_present & WPAD_DATA_EXPANSION) {
		switch(data->exp.type) {
			case EXP_NUNCHUK:
			{
				struct nunchuk_t *nc = &data->exp.nunchuk;

				nc->orient = lstate->exp.nunchuk.orient;
				calc_joystick_state(&nc->js,nc->js.pos.x,nc->js.pos.y);
				calculate_orientation(&nc->accel_calib,&nc->accel,&nc->orient,smoothed);
				calculate_gforce(&nc->accel_calib,&nc->accel,&nc->gforce);
				data->btns_h |= (data->exp.nunchuk.btns<<16);
			}
			break;

			case EXP_CLASSIC:
			{
				struct classic_ctrl_t *cc = &data->exp.classic;

				cc->r_shoulder = ((f32)cc->rs_raw/0x1F);
				cc->l_shoulder = ((f32)cc->ls_raw/0x1F);
				calc_joystick_state(&cc->ljs, cc->ljs.pos.x, cc->ljs.pos.y);
				calc_joystick_state(&cc->rjs, cc->rjs.pos.x, cc->rjs.pos.y);
				data->btns_h |= (data->exp.classic.btns<<16);
			}
			break;
			default:
				break;
		}
	}
	*lstate = *data;
}