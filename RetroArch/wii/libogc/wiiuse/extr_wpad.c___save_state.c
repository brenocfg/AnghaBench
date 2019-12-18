#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int /*<<< orphan*/  mp; int /*<<< orphan*/  classic; int /*<<< orphan*/  nunchuk; } ;
struct TYPE_4__ {int /*<<< orphan*/  mp; int /*<<< orphan*/  classic; int /*<<< orphan*/  nunchuk; } ;
struct TYPE_6__ {TYPE_1__ exp; int /*<<< orphan*/  ir; int /*<<< orphan*/  accel; int /*<<< orphan*/  btns; } ;
struct wiimote_t {TYPE_2__ exp; TYPE_3__ lstate; int /*<<< orphan*/  ir; int /*<<< orphan*/  accel; int /*<<< orphan*/  btns; } ;

/* Variables and functions */
#define  EXP_CLASSIC 130 
#define  EXP_MOTION_PLUS 129 
#define  EXP_NUNCHUK 128 

__attribute__((used)) static void __save_state(struct wiimote_t* wm) {
	/* wiimote */
	wm->lstate.btns = wm->btns;
	wm->lstate.accel = wm->accel;

	/* ir */
	wm->lstate.ir = wm->ir;

	/* expansion */
	switch (wm->exp.type) {
		case EXP_NUNCHUK:
			wm->lstate.exp.nunchuk = wm->exp.nunchuk;
			break;
		case EXP_CLASSIC:
			wm->lstate.exp.classic = wm->exp.classic;
			break;
		case EXP_MOTION_PLUS:
			wm->lstate.exp.mp = wm->exp.mp;
			break;
	}
}