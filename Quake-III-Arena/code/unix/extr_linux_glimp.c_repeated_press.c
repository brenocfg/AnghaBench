#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ keycode; scalar_t__ time; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ xkey; } ;
typedef  TYPE_2__ XEvent ;

/* Variables and functions */
 scalar_t__ KeyPress ; 
 scalar_t__ X11_PendingInput () ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  XPeekEvent (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dpy ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean repeated_press(XEvent *event)
{
  XEvent        peekevent;
  qboolean      repeated = qfalse;

  assert(dpy != NULL);

  if (X11_PendingInput())
  {
    XPeekEvent(dpy, &peekevent);

    if ((peekevent.type == KeyPress) &&
        (peekevent.xkey.keycode == event->xkey.keycode) &&
        (peekevent.xkey.time == event->xkey.time))
    {
      repeated = qtrue;
      XNextEvent(dpy, &peekevent);  // skip event.
    } // if
  } // if

  return(repeated);
}