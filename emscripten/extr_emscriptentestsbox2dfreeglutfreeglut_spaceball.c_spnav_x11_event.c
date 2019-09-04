#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int press; int /*<<< orphan*/  bnum; } ;
struct TYPE_9__ {int /*<<< orphan*/  period; int /*<<< orphan*/ * data; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {int type; TYPE_2__ button; TYPE_1__ motion; } ;
typedef  TYPE_5__ spnav_event ;
struct TYPE_11__ {int /*<<< orphan*/ * s; } ;
struct TYPE_12__ {int message_type; TYPE_3__ data; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_4__ xclient; } ;
typedef  TYPE_6__ XEvent ;

/* Variables and functions */
 scalar_t__ ClientMessage ; 
 int SPNAV_EVENT_BUTTON ; 
 int SPNAV_EVENT_MOTION ; 
 int button_press_event ; 
 int button_release_event ; 
 int motion_event ; 

__attribute__((used)) static int spnav_x11_event(const XEvent *xev, spnav_event *event)
{
  int i;
  int xmsg_type;

  if(xev->type != ClientMessage) {
    return 0;
  }

  xmsg_type = xev->xclient.message_type;

  if(xmsg_type != motion_event && xmsg_type != button_press_event &&
      xmsg_type != button_release_event) {
    return 0;
  }

  if(xmsg_type == motion_event) {
    event->type = SPNAV_EVENT_MOTION;
    event->motion.data = &event->motion.x;

    for(i=0; i<6; i++) {
      event->motion.data[i] = xev->xclient.data.s[i + 2];
    }
    event->motion.period = xev->xclient.data.s[8];
  } else {
    event->type = SPNAV_EVENT_BUTTON;
    event->button.press = xmsg_type == button_press_event ? 1 : 0;
    event->button.bnum = xev->xclient.data.s[2];
  }
  return event->type;
}