#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XEvent ;

/* Variables and functions */
 scalar_t__ XCheckIfEvent (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dpy ; 
 int /*<<< orphan*/  match_events ; 

__attribute__((used)) static int spnav_remove_events(int type)
{
  int rm_count = 0;

  if(dpy) {
    XEvent xev;

    while(XCheckIfEvent(dpy, &xev, match_events, (char*)&type)) {
      rm_count++;
    }
    return rm_count;
  }
  return 0;
}