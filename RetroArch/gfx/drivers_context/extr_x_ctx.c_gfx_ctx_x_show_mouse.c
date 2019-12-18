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

/* Variables and functions */
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  g_x11_win ; 
 int /*<<< orphan*/  x11_show_mouse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfx_ctx_x_show_mouse(void *data, bool state)
{
   x11_show_mouse(g_x11_dpy, g_x11_win, state);
}