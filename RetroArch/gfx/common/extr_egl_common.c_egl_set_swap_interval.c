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
struct TYPE_3__ {int interval; scalar_t__ dpy; } ;
typedef  TYPE_1__ egl_ctx_data_t ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
 int /*<<< orphan*/  eglGetCurrentContext () ; 
 int /*<<< orphan*/  eglSwapInterval (scalar_t__,int) ; 
 int /*<<< orphan*/  egl_report_error () ; 

void egl_set_swap_interval(egl_ctx_data_t *egl, int interval)
{
   /* Can be called before initialization.
    * Some contexts require that swap interval
    * is known at startup time.
    */
   egl->interval = interval;

   if (egl->dpy  == EGL_NO_DISPLAY)
      return;
   if (!(eglGetCurrentContext()))
      return;

   RARCH_LOG("[EGL]: eglSwapInterval(%u)\n", interval);
   if (!eglSwapInterval(egl->dpy, interval))
   {
      RARCH_ERR("[EGL]: eglSwapInterval() failed.\n");
      egl_report_error();
   }
}