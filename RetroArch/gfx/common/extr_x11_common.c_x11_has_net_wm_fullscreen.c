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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XA_NET_WM_STATE_FULLSCREEN ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int x11_check_atom_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool x11_has_net_wm_fullscreen(Display *dpy)
{
   XA_NET_WM_STATE_FULLSCREEN = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);

   return x11_check_atom_supported(dpy, XA_NET_WM_STATE_FULLSCREEN);
}