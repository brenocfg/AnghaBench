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
typedef  int /*<<< orphan*/  uword ;
typedef  int ubyte ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct wiimote_t {TYPE_1__ exp; int /*<<< orphan*/  event; int /*<<< orphan*/  motion_plus_id; } ;

/* Variables and functions */
 int EXP_ID_CODE_MOTION_PLUS ; 
 int /*<<< orphan*/  EXP_MOTION_PLUS ; 
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_FAILED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_HANDSHAKE ; 
 int /*<<< orphan*/  WIIUSE_MOTION_PLUS_ACTIVATED ; 
 int /*<<< orphan*/  WM_EXP_ID ; 
 int /*<<< orphan*/  wiiuse_read_data (struct wiimote_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void (*) (struct wiimote_t*,int*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  wiiuse_set_ir_mode (struct wiimote_t*) ; 

void wiiuse_motion_plus_check(struct wiimote_t *wm,ubyte *data,uword len)
{
	u32 val;
	if(data == NULL)
	{
		wiiuse_read_data(wm, wm->motion_plus_id, WM_EXP_ID, 6, wiiuse_motion_plus_check);
	}
	else
	{
		WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_EXP);
		WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_EXP_FAILED);
		WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_EXP_HANDSHAKE);
		val = (data[3] << 16) | (data[2] << 24) | (data[4] << 8) | data[5];
		if(val == EXP_ID_CODE_MOTION_PLUS)
		{
			/* handshake done */
			wm->event = WIIUSE_MOTION_PLUS_ACTIVATED;
			wm->exp.type = EXP_MOTION_PLUS;

			WIIMOTE_ENABLE_STATE(wm,WIIMOTE_STATE_EXP);
			wiiuse_set_ir_mode(wm);
		}
	}
}