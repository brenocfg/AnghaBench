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
typedef  int (* RUN_APP_FN_T ) (void const*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  EGL_DISPMANX_WINDOW_T ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_host_init () ; 
 scalar_t__ create_native_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,...) ; 

int runApp(const char *name, RUN_APP_FN_T run_app_fn, const void *params, size_t param_size)
{
   EGL_DISPMANX_WINDOW_T win;
   (void) param_size;

   vcos_log_trace("Initialsing BCM HOST");
   bcm_host_init();

   vcos_log_trace("Starting '%s'", name);
   if (create_native_window(&win) != 0)
      return -1;

   return run_app_fn(params, (EGLNativeWindowType *) &win);
}