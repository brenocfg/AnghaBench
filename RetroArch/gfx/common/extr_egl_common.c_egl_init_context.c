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
struct TYPE_3__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  config; scalar_t__ dpy; } ;
typedef  TYPE_1__ egl_ctx_data_t ;
typedef  scalar_t__ (* egl_accept_config_cb_t ) (void*,scalar_t__,int /*<<< orphan*/ ) ;
typedef  int EGLint ;
typedef  int /*<<< orphan*/  EGLenum ;
typedef  scalar_t__ EGLDisplay ;
typedef  int /*<<< orphan*/  EGLConfig ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,int) ; 
 int /*<<< orphan*/  eglChooseConfig (scalar_t__,int const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  eglGetConfigs (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  eglInitialize (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_egl_major ; 
 int /*<<< orphan*/  g_egl_minor ; 
 scalar_t__ get_egl_display (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ malloc (int) ; 

bool egl_init_context(egl_ctx_data_t *egl,
      EGLenum platform,
      void *display_data,
      EGLint *major, EGLint *minor,
      EGLint *count, const EGLint *attrib_ptr,
      egl_accept_config_cb_t cb)
{
   EGLint i;
   EGLConfig *configs = NULL;
   EGLint matched     = 0;
   int config_index   = -1;
   EGLDisplay dpy     = get_egl_display(platform, display_data);

   if (dpy == EGL_NO_DISPLAY)
   {
      RARCH_ERR("[EGL]: Couldn't get EGL display.\n");
      return false;
   }

   egl->dpy = dpy;

   if (!eglInitialize(egl->dpy, major, minor))
      return false;

   RARCH_LOG("[EGL]: EGL version: %d.%d\n", *major, *minor);

   if (!eglGetConfigs(egl->dpy, NULL, 0, count) || *count < 1)
   {
      RARCH_ERR("[EGL]: No configs to choose from.\n");
      return false;
   }

   configs = (EGLConfig*)malloc(*count * sizeof(*configs));
   if (!configs)
      return false;

   if (!eglChooseConfig(egl->dpy, attrib_ptr,
            configs, *count, &matched) || !matched)
   {
      RARCH_ERR("[EGL]: No EGL configs with appropriate attributes.\n");
      return false;
   }

   for (i = 0; i < *count; i++)
   {
      if (!cb || cb(display_data, egl->dpy, configs[i]))
      {
         egl->config = configs[i];
         break;
      }
   }

   free(configs);

   if (i == *count)
   {
      RARCH_ERR("[EGL]: No EGL config found which satifies requirements.\n");
      return false;
   }

   egl->major = g_egl_major;
   egl->minor = g_egl_minor;

   return true;
}