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
struct TYPE_2__ {scalar_t__ port; } ;
typedef  TYPE_1__ xv_t ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ XInternAtom (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XvSetPortAttribute (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  g_x11_dpy ; 

__attribute__((used)) static void xv_set_nonblock_state(void *data, bool state)
{
   xv_t *xv  = (xv_t*)data;
   Atom atom = XInternAtom(g_x11_dpy, "XV_SYNC_TO_VBLANK", true);

   if (atom != None && xv->port)
      XvSetPortAttribute(g_x11_dpy, xv->port, atom, !state);
   else
      RARCH_WARN("Failed to set SYNC_TO_VBLANK attribute.\n");
}