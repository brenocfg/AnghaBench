#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uword ;
typedef  int ubyte ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int x; int y; int z; } ;
struct TYPE_14__ {int x; int y; int z; } ;
struct TYPE_16__ {TYPE_7__ cal_g; TYPE_6__ cal_zero; } ;
struct wiimote_t {TYPE_1__ exp; int /*<<< orphan*/  event; TYPE_8__ accel_calib; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int x; int y; } ;
struct TYPE_11__ {int x; int y; } ;
struct TYPE_10__ {int x; int y; } ;
struct TYPE_13__ {TYPE_4__ center; TYPE_3__ min; TYPE_2__ max; } ;
struct nunchuk_t {TYPE_5__ js; TYPE_8__ accel_calib; int /*<<< orphan*/ * flags; scalar_t__ btns_released; scalar_t__ btns_held; scalar_t__ btns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_HANDSHAKE_LEN ; 
 int /*<<< orphan*/  EXP_NUNCHUK ; 
 int /*<<< orphan*/  WIIUSE_NUNCHUK_INSERTED ; 
 int /*<<< orphan*/  WM_EXP_MEM_CALIBR ; 
 int /*<<< orphan*/  wiiuse_handshake_expansion ; 
 int /*<<< orphan*/  wiiuse_read_data (struct wiimote_t*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nunchuk_handshake(struct wiimote_t *wm,struct nunchuk_t *nc,ubyte *data,uword len)
{
	//int i;
	int offset = 0;

	nc->btns = 0;
	nc->btns_held = 0;
	nc->btns_released = 0;
	nc->flags = &wm->flags;
	nc->accel_calib = wm->accel_calib;

	//for(i=0;i<len;i++) data[i] = (data[i]^0x17)+0x17;
	if(data[offset]==0xff) {
		if(data[offset+16]==0xff) {
			// try to read the calibration data again
			wiiuse_read_data(wm,data,WM_EXP_MEM_CALIBR,EXP_HANDSHAKE_LEN,wiiuse_handshake_expansion);
		} else
			offset += 16;
	}

	nc->accel_calib.cal_zero.x = (data[offset + 0]<<2)|((data[offset + 3]>>4)&3);
	nc->accel_calib.cal_zero.y = (data[offset + 1]<<2)|((data[offset + 3]>>2)&3);
	nc->accel_calib.cal_zero.z = (data[offset + 2]<<2)|(data[offset + 3]&3);
	nc->accel_calib.cal_g.x = (data[offset + 4]<<2)|((data[offset + 7]>>4)&3);
	nc->accel_calib.cal_g.y = (data[offset + 5]<<2)|((data[offset + 7]>>2)&3);
	nc->accel_calib.cal_g.z = (data[offset + 6]<<2)|(data[offset + 7]&3);
	nc->js.max.x = data[offset + 8];
	nc->js.min.x = data[offset + 9];
	nc->js.center.x = data[offset + 10];
	nc->js.max.y = data[offset + 11];
	nc->js.min.y = data[offset + 12];
	nc->js.center.y = data[offset + 13];

	// set to defaults (averages from 5 nunchuks) if calibration data is invalid
	if(nc->accel_calib.cal_zero.x == 0)
		nc->accel_calib.cal_zero.x = 499;
	if(nc->accel_calib.cal_zero.y == 0)
		nc->accel_calib.cal_zero.y = 509;
	if(nc->accel_calib.cal_zero.z == 0)
		nc->accel_calib.cal_zero.z = 507;
	if(nc->accel_calib.cal_g.x == 0)
		nc->accel_calib.cal_g.x = 703;
	if(nc->accel_calib.cal_g.y == 0)
		nc->accel_calib.cal_g.y = 709;
	if(nc->accel_calib.cal_g.z == 0)
		nc->accel_calib.cal_g.z = 709;
	if(nc->js.max.x == 0)
		nc->js.max.x = 223;
	if(nc->js.min.x == 0)
		nc->js.min.x = 27;
	if(nc->js.center.x == 0)
		nc->js.center.x = 126;
	if(nc->js.max.y == 0)
		nc->js.max.y = 222;
	if(nc->js.min.y == 0)
		nc->js.min.y = 30;
	if(nc->js.center.y == 0)
		nc->js.center.y = 131;

	wm->event = WIIUSE_NUNCHUK_INSERTED;
	wm->exp.type = EXP_NUNCHUK;

	return 1;
}