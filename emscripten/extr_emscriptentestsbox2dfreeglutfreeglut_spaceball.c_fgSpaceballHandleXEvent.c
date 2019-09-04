#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bnum; int /*<<< orphan*/  press; } ;
struct TYPE_5__ {int x; int y; int z; int rx; int ry; int rz; } ;
struct TYPE_7__ {int type; TYPE_2__ button; TYPE_1__ motion; } ;
typedef  TYPE_3__ spnav_event ;
typedef  int /*<<< orphan*/  XEvent ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_DOWN ; 
 int /*<<< orphan*/  GLUT_UP ; 
 int /*<<< orphan*/  INVOKE_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  SPNAV_EVENT_BUTTON 129 
#define  SPNAV_EVENT_MOTION 128 
 int /*<<< orphan*/  SpaceButton ; 
 int /*<<< orphan*/  SpaceMotion ; 
 int /*<<< orphan*/  SpaceRotation ; 
 int /*<<< orphan*/  fgInitialiseSpaceball () ; 
 int /*<<< orphan*/  sball_initialized ; 
 int /*<<< orphan*/  spnav_remove_events (int const) ; 
 int /*<<< orphan*/ * spnav_win ; 
 scalar_t__ spnav_x11_event (int /*<<< orphan*/  const*,TYPE_3__*) ; 

void fgSpaceballHandleXEvent(const XEvent *xev)
{
    spnav_event sev;

    if(!sball_initialized) {
        fgInitialiseSpaceball();
        if(!sball_initialized) {
            return;
        }
    }

    if(spnav_x11_event(xev, &sev)) {
        switch(sev.type) {
        case SPNAV_EVENT_MOTION:
            if(sev.motion.x | sev.motion.y | sev.motion.z) {
                INVOKE_WCB(*spnav_win, SpaceMotion, (sev.motion.x, sev.motion.y, sev.motion.z));
            }
            if(sev.motion.rx | sev.motion.ry | sev.motion.rz) {
                INVOKE_WCB(*spnav_win, SpaceRotation, (sev.motion.rx, sev.motion.ry, sev.motion.rz));
            }
            spnav_remove_events(SPNAV_EVENT_MOTION);
            break;

        case SPNAV_EVENT_BUTTON:
            INVOKE_WCB(*spnav_win, SpaceButton, (sev.button.bnum, sev.button.press ? GLUT_DOWN : GLUT_UP));
            break;

        default:
            break;
        }
    }
}