#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ value; } ;
typedef  TYPE_1__ XTextProperty ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AnyPropertyType ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XFree (unsigned char*) ; 
 int /*<<< orphan*/  XGetWMName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XGetWindowProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,unsigned long*,unsigned long*,unsigned char**) ; 
 int /*<<< orphan*/  command_event ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static Window get_daemon_window(Display *dpy)
{
  Window win, root_win;
  XTextProperty wname;
  Atom type;
  int fmt;
  unsigned long nitems, bytes_after;
  unsigned char *prop;

  root_win = DefaultRootWindow(dpy);

  XGetWindowProperty(dpy, root_win, command_event, 0, 1, False, AnyPropertyType, &type, &fmt, &nitems, &bytes_after, &prop);
  if(!prop) {
    return 0;
  }

  win = *(Window*)prop;
  XFree(prop);

  if(!XGetWMName(dpy, win, &wname) || strcmp("Magellan Window", (char*)wname.value) != 0) {
    return 0;
  }

  return win;
}