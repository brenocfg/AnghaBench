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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_1__ EGL_DISPMANX_WINDOW_T ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLDisplay ;

/* Variables and functions */
 TYPE_1__* check_default (int /*<<< orphan*/ ) ; 

void platform_get_dimensions(EGLDisplay dpy, EGLNativeWindowType win,
      uint32_t *width, uint32_t *height, uint32_t *swapchain_count)
{
   EGL_DISPMANX_WINDOW_T *dwin = check_default(win);

   *width =  dwin->width;
   *height = dwin->height;
   *swapchain_count = 0;
}