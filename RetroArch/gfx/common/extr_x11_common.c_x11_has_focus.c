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
typedef  scalar_t__ Window ;

/* Variables and functions */
 int /*<<< orphan*/  XGetInputFocus (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 scalar_t__ g_x11_has_focus ; 
 scalar_t__ g_x11_true_full ; 
 scalar_t__ g_x11_win ; 

bool x11_has_focus(void *data)
{
   Window win;
   int rev;

   XGetInputFocus(g_x11_dpy, &win, &rev);

   return (win == g_x11_win && g_x11_has_focus) || g_x11_true_full;
}