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
struct TYPE_2__ {int type; int /*<<< orphan*/  mp; int /*<<< orphan*/  classic; int /*<<< orphan*/  nunchuk; } ;
struct wiimote_t {TYPE_1__ exp; int /*<<< orphan*/  event; } ;

/* Variables and functions */
#define  EXP_CLASSIC 130 
#define  EXP_MOTION_PLUS 129 
 int EXP_NONE ; 
#define  EXP_NUNCHUK 128 
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIUSE_CLASSIC_CTRL_REMOVED ; 
 int /*<<< orphan*/  WIIUSE_MOTION_PLUS_REMOVED ; 
 int /*<<< orphan*/  WIIUSE_NUNCHUK_REMOVED ; 
 int /*<<< orphan*/  classic_ctrl_disconnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  motion_plus_disconnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nunchuk_disconnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_set_ir_mode (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,int /*<<< orphan*/ *) ; 

void wiiuse_disable_expansion(struct wiimote_t *wm)
{
	if(!WIIMOTE_IS_SET(wm, WIIMOTE_STATE_EXP)) return;

	/* tell the associated module the expansion was removed */
	switch(wm->exp.type) {
		case EXP_NUNCHUK:
			nunchuk_disconnected(&wm->exp.nunchuk);
			wm->event = WIIUSE_NUNCHUK_REMOVED;
			break;
		case EXP_CLASSIC:
			classic_ctrl_disconnected(&wm->exp.classic);
			wm->event = WIIUSE_CLASSIC_CTRL_REMOVED;
			break;
		case EXP_MOTION_PLUS:
 			motion_plus_disconnected(&wm->exp.mp);
 			wm->event = WIIUSE_MOTION_PLUS_REMOVED;
 			break;

		default:
			break;
	}

	WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_EXP);
	wm->exp.type = EXP_NONE;

	wiiuse_set_ir_mode(wm);
	wiiuse_status(wm,NULL);
}