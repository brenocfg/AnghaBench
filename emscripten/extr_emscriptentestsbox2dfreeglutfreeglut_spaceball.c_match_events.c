#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ message_type; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ xclient; } ;
typedef  TYPE_2__ XEvent ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 scalar_t__ ClientMessage ; 
 int /*<<< orphan*/  False ; 
 int SPNAV_EVENT_BUTTON ; 
 int SPNAV_EVENT_MOTION ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ button_press_event ; 
 scalar_t__ button_release_event ; 
 scalar_t__ motion_event ; 

__attribute__((used)) static Bool match_events(Display *dpy, XEvent *xev, char *arg)
{
  int evtype = *(int*)arg;

  if(xev->type != ClientMessage) {
    return False;
  }

  if(xev->xclient.message_type == motion_event) {
    return !evtype || evtype == SPNAV_EVENT_MOTION ? True : False;
  }
  if(xev->xclient.message_type == button_press_event ||
      xev->xclient.message_type == button_release_event) {
    return !evtype || evtype == SPNAV_EVENT_BUTTON ? True : False;
  }
  return False;
}