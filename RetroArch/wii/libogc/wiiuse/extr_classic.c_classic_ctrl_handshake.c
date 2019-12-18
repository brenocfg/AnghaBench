#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uword ;
typedef  int ubyte ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct wiimote_t {int /*<<< orphan*/  timeout; TYPE_5__ exp; int /*<<< orphan*/  event; } ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_9__ {TYPE_3__ center; TYPE_2__ min; TYPE_1__ max; } ;
struct classic_ctrl_t {int type; TYPE_4__ rjs; TYPE_4__ ljs; scalar_t__ btns_released; scalar_t__ btns_held; scalar_t__ btns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_CLASSIC ; 
 int /*<<< orphan*/  EXP_HANDSHAKE_LEN ; 
 int /*<<< orphan*/  WIIMOTE_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  WIIUSE_CLASSIC_CTRL_INSERTED ; 
 int /*<<< orphan*/  WIIUSE_DEBUG (char*) ; 
 int /*<<< orphan*/  WM_EXP_MEM_CALIBR ; 
 int /*<<< orphan*/  wiiuse_handshake_expansion ; 
 int /*<<< orphan*/  wiiuse_read_data (struct wiimote_t*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int classic_ctrl_handshake(struct wiimote_t* wm, struct classic_ctrl_t* cc, ubyte* data, uword len) {
	//int i;
	int offset = 0;

	cc->btns = 0;
	cc->btns_held = 0;
	cc->btns_released = 0;

	/* decrypt data */
	/*
	for (i = 0; i < len; ++i)
		data[i] = (data[i] ^ 0x17) + 0x17;
	*/

	/* is this a wiiu pro? */
	if (len > 223 && data[223] == 0x20) {
		cc->ljs.max.x = cc->ljs.max.y = 0xFF;
		cc->ljs.min.x = cc->ljs.min.y = 0;
		cc->ljs.center.x = cc->ljs.center.y = 0x80;

		cc->rjs = cc->ljs;

		cc->type = 2;
	}
	else {
		if (data[offset] == 0xFF) {
			/*
			*	Sometimes the data returned here is not correct.
			*	This might happen because the wiimote is lagging
			*	behind our initialization sequence.
			*	To fix this just request the handshake again.
			*
			*	Other times it's just the first 16 bytes are 0xFF,
			*	but since the next 16 bytes are the same, just use
			*	those.
			*/
			if (data[offset + 16] == 0xFF) {
				/* get the calibration data again */
				WIIUSE_DEBUG("Classic controller handshake appears invalid, trying again.");
				wiiuse_read_data(wm, data, WM_EXP_MEM_CALIBR, EXP_HANDSHAKE_LEN, wiiuse_handshake_expansion);
			} else
				offset += 16;
		}

		if (len > 218 && data[218])
			cc->type = 1; /* classic controller pro (no analog triggers) */
		else
			cc->type = 0; /* original classic controller (analog triggers) */

		/* joystick stuff */
		cc->ljs.max.x = data[0 + offset] / 4 == 0 ? 64 : data[0 + offset] / 4;
		cc->ljs.min.x = data[1 + offset] / 4;
		cc->ljs.center.x = data[2 + offset] / 4 == 0 ? 32 : data[2 + offset] / 4;
		cc->ljs.max.y = data[3 + offset] / 4 == 0 ? 64 : data[3 + offset] / 4;
		cc->ljs.min.y = data[4 + offset] / 4;
		cc->ljs.center.y = data[5 + offset] / 4 == 0 ? 32 : data[5 + offset] / 4;

		cc->rjs.max.x = data[6 + offset] / 8 == 0 ? 32 : data[6 + offset] / 8;
		cc->rjs.min.x = data[7 + offset] / 8;
		cc->rjs.center.x = data[8 + offset] / 8 == 0 ? 16 : data[8 + offset] / 8;
		cc->rjs.max.y = data[9 + offset] / 8 == 0 ? 32 : data[9 + offset] / 8;
		cc->rjs.min.y = data[10 + offset] / 8;
		cc->rjs.center.y = data[11 + offset] / 8 == 0 ? 16 : data[11 + offset] / 8;
	}
	/* handshake done */
	wm->event = WIIUSE_CLASSIC_CTRL_INSERTED;
	wm->exp.type = EXP_CLASSIC;

	#ifdef WIN32
	wm->timeout = WIIMOTE_DEFAULT_TIMEOUT;
	#endif

	return 1;
}