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
typedef  int /*<<< orphan*/  ubyte ;
struct TYPE_2__ {int type; int /*<<< orphan*/  mp; int /*<<< orphan*/  classic; int /*<<< orphan*/  nunchuk; } ;
struct wiimote_t {TYPE_1__ exp; } ;

/* Variables and functions */
#define  EXP_CLASSIC 130 
#define  EXP_MOTION_PLUS 129 
#define  EXP_NUNCHUK 128 
 int /*<<< orphan*/  classic_ctrl_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  motion_plus_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nunchuk_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_expansion(struct wiimote_t *wm,ubyte *msg)
{
	switch (wm->exp.type) {
		case EXP_NUNCHUK:
			nunchuk_event(&wm->exp.nunchuk, msg);
			break;
		case EXP_CLASSIC:
			classic_ctrl_event(&wm->exp.classic, msg);
			break;
 		case EXP_MOTION_PLUS:
 			motion_plus_event(&wm->exp.mp, msg);
 			break;
		default:
			break;
	}
}