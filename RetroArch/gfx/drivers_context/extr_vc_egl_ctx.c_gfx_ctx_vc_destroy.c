#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ config; int /*<<< orphan*/ * dpy; int /*<<< orphan*/ * surf; int /*<<< orphan*/ * hw_ctx; int /*<<< orphan*/ * ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsync_condition; int /*<<< orphan*/  vsync_condition_mutex; int /*<<< orphan*/  dispman_display; scalar_t__ vsync_callback_set; scalar_t__* vgimage; int /*<<< orphan*/ ** eglBuffer; TYPE_1__ egl; int /*<<< orphan*/ * pbuff_surf; int /*<<< orphan*/ * eglimage_ctx; } ;
typedef  TYPE_2__ vc_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EGL_NO_CONTEXT ; 
 int /*<<< orphan*/ * EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_OPENVG_API ; 
 unsigned int MAX_EGLIMAGE_TEXTURES ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ *) ; 
 int g_egl_inited ; 
 int /*<<< orphan*/  gfx_ctx_vc_bind_api (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peglDestroyImageKHR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_api ; 
 int /*<<< orphan*/  vc_dispmanx_vsync_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgDestroyImage (scalar_t__) ; 

__attribute__((used)) static void gfx_ctx_vc_destroy(void *data)
{
   vc_ctx_data_t *vc = (vc_ctx_data_t*)data;
   unsigned i;

   if (!vc)
   {
       g_egl_inited = false;
       return;
   }

   if (vc->egl.dpy)
   {
      for (i = 0; i < MAX_EGLIMAGE_TEXTURES; i++)
      {
         if (vc->eglBuffer[i] && peglDestroyImageKHR)
         {
            eglBindAPI(EGL_OPENVG_API);
            eglMakeCurrent(vc->egl.dpy,
                  vc->pbuff_surf, vc->pbuff_surf, vc->eglimage_ctx);
            peglDestroyImageKHR(vc->egl.dpy, vc->eglBuffer[i]);
         }

         if (vc->vgimage[i])
         {
            eglBindAPI(EGL_OPENVG_API);
            eglMakeCurrent(vc->egl.dpy,
                  vc->pbuff_surf, vc->pbuff_surf, vc->eglimage_ctx);
            vgDestroyImage(vc->vgimage[i]);
         }
      }

      if (vc->egl.ctx)
      {
         gfx_ctx_vc_bind_api(data, vc_api, 0, 0);
         eglMakeCurrent(vc->egl.dpy,
               EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
         eglDestroyContext(vc->egl.dpy, vc->egl.ctx);
      }

      if (vc->egl.hw_ctx)
         eglDestroyContext(vc->egl.dpy, vc->egl.hw_ctx);

      if (vc->eglimage_ctx)
      {
         eglBindAPI(EGL_OPENVG_API);
         eglMakeCurrent(vc->egl.dpy,
               EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
         eglDestroyContext(vc->egl.dpy, vc->eglimage_ctx);
      }

      if (vc->egl.surf)
      {
         gfx_ctx_vc_bind_api(data, vc_api, 0, 0);
         eglDestroySurface(vc->egl.dpy, vc->egl.surf);
      }

      if (vc->pbuff_surf)
      {
         eglBindAPI(EGL_OPENVG_API);
         eglDestroySurface(vc->egl.dpy, vc->pbuff_surf);
      }

      eglBindAPI(EGL_OPENVG_API);
      eglMakeCurrent(vc->egl.dpy,
            EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      gfx_ctx_vc_bind_api(data, vc_api, 0, 0);
      eglMakeCurrent(vc->egl.dpy,
            EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      eglTerminate(vc->egl.dpy);
   }

   vc->egl.ctx      = NULL;
   vc->egl.hw_ctx   = NULL;
   vc->eglimage_ctx = NULL;
   vc->egl.surf     = NULL;
   vc->pbuff_surf   = NULL;
   vc->egl.dpy      = NULL;
   vc->egl.config   = 0;
   g_egl_inited     = false;

   for (i = 0; i < MAX_EGLIMAGE_TEXTURES; i++)
   {
      vc->eglBuffer[i] = NULL;
      vc->vgimage[i]   = 0;
   }

   /* Stop generating vsync callbacks if we are doing so.
    * Don't destroy the context while cbs are being generated! */
   if (vc->vsync_callback_set)
      vc_dispmanx_vsync_callback(vc->dispman_display, NULL, NULL);

   /* Destroy mutexes and conditions. */
   slock_free(vc->vsync_condition_mutex);
   scond_free(vc->vsync_condition);
}