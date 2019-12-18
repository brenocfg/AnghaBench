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
typedef  int uword ;
typedef  int ubyte ;
struct TYPE_4__ {int x; int y; int z; } ;
struct TYPE_3__ {int x; int y; int z; } ;
struct accel_t {TYPE_2__ cal_zero; TYPE_1__ cal_g; } ;
struct wiimote_t {int handshake_state; int /*<<< orphan*/  event; struct accel_t accel_calib; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIG_ENDIAN_LONG (int) ; 
 int /*<<< orphan*/  EXP_ID_CODE_CLASSIC_WIIU_PRO ; 
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_LED_NONE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_WIIU_PRO ; 
 int /*<<< orphan*/  WIIUSE_CONNECT ; 
 int WM_CTRL_STATUS_BYTE1_ATTACHMENT ; 
 int /*<<< orphan*/  WM_EXP_ID ; 
 int /*<<< orphan*/  WM_MEM_OFFSET_CALIBRATION ; 
 int* __lwp_wkspace_allocate (int) ; 
 int /*<<< orphan*/  __lwp_wkspace_free (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiiuse_read_data (struct wiimote_t*,int*,int /*<<< orphan*/ ,int,void (*) (struct wiimote_t*,int*,int)) ; 
 int /*<<< orphan*/  wiiuse_set_leds (struct wiimote_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,void (*) (struct wiimote_t*,int*,int)) ; 

void wiiuse_handshake(struct wiimote_t *wm,ubyte *data,uword len)
{
	ubyte *buf = NULL;
	struct accel_t *accel = &wm->accel_calib;

	//printf("wiiuse_handshake(%d,%p,%d)\n",wm->handshake_state,data,len);

	switch(wm->handshake_state) {
		case 0:
			wm->handshake_state++;

			wiiuse_set_leds(wm,WIIMOTE_LED_NONE,NULL);
			wiiuse_status(wm,wiiuse_handshake);
			return;

		case 1:
			wm->handshake_state++;
			buf = __lwp_wkspace_allocate(sizeof(ubyte)*8);

			if (len > 2 && data[2]&WM_CTRL_STATUS_BYTE1_ATTACHMENT) {
				wiiuse_read_data(wm,buf,WM_EXP_ID,6,wiiuse_handshake);
				return;

		case 2:
				if (BIG_ENDIAN_LONG(*(int*)(&data[2])) == EXP_ID_CODE_CLASSIC_WIIU_PRO) {
					memset(data, 0, 8);
					WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_WIIU_PRO);
					break;
				}
				buf = data;
			}

			wm->handshake_state++;
			wiiuse_read_data(wm,buf,WM_MEM_OFFSET_CALIBRATION,7,wiiuse_handshake);
			return;
	}

	accel->cal_zero.x = ((data[0]<<2)|((data[3]>>4)&3));
	accel->cal_zero.y = ((data[1]<<2)|((data[3]>>2)&3));
	accel->cal_zero.z = ((data[2]<<2)|(data[3]&3));

	accel->cal_g.x = (((data[4]<<2)|((data[7]>>4)&3)) - accel->cal_zero.x);
	accel->cal_g.y = (((data[5]<<2)|((data[7]>>2)&3)) - accel->cal_zero.y);
	accel->cal_g.z = (((data[6]<<2)|(data[7]&3)) - accel->cal_zero.z);
	__lwp_wkspace_free(data);

	WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_HANDSHAKE);
	WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_HANDSHAKE_COMPLETE);

	wm->event = WIIUSE_CONNECT;
	wiiuse_status(wm,NULL);
}