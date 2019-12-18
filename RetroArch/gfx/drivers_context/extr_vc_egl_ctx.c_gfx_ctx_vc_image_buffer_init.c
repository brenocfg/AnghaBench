#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int input_scale; int /*<<< orphan*/  smooth; } ;
typedef  TYPE_2__ video_info_t ;
struct TYPE_6__ {scalar_t__ surf; scalar_t__ ctx; int /*<<< orphan*/  dpy; int /*<<< orphan*/  config; } ;
struct TYPE_8__ {int res; scalar_t__ pbuff_surf; scalar_t__ eglimage_ctx; TYPE_1__ egl; int /*<<< orphan*/  smooth; } ;
typedef  TYPE_3__ vc_ctx_data_t ;
typedef  scalar_t__ PFNEGLDESTROYIMAGEKHRPROC ;
typedef  scalar_t__ PFNEGLCREATEIMAGEKHRPROC ;
typedef  int EGLint ;
typedef  scalar_t__ EGLBoolean ;

/* Variables and functions */
 scalar_t__ EGL_FALSE ; 
 int EGL_HEIGHT ; 
 int EGL_NONE ; 
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 int /*<<< orphan*/  EGL_OPENVG_API ; 
 int EGL_WIDTH ; 
 scalar_t__ GFX_CTX_OPENVG_API ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int RARCH_SCALE_BASE ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 scalar_t__ eglCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eglCreatePbufferSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eglMakeCurrent (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ egl_get_proc_address (char*) ; 
 int /*<<< orphan*/  gfx_ctx_vc_bind_api (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_ctx_vc_egl_query_extension (TYPE_3__*,char*) ; 
 scalar_t__ peglCreateImageKHR ; 
 scalar_t__ peglDestroyImageKHR ; 
 scalar_t__ vc_api ; 

__attribute__((used)) static bool gfx_ctx_vc_image_buffer_init(void *data,
      const video_info_t *video)
{
   EGLBoolean result;
   vc_ctx_data_t *vc = (vc_ctx_data_t*)data;
   EGLint pbufsurface_list[] =
   {
      EGL_WIDTH, vc->res,
      EGL_HEIGHT, vc->res,
      EGL_NONE
   };

   /* Don't bother, we just use VGImages for our EGLImage anyway. */
   if (vc_api == GFX_CTX_OPENVG_API)
      return false;

   peglCreateImageKHR  = (PFNEGLCREATEIMAGEKHRPROC)egl_get_proc_address("eglCreateImageKHR");
   peglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)egl_get_proc_address("eglDestroyImageKHR");

   if (  !peglCreateImageKHR  ||
         !peglDestroyImageKHR ||
         !gfx_ctx_vc_egl_query_extension(vc, "KHR_image")
      )
      return false;

   vc->res = video->input_scale * RARCH_SCALE_BASE;

   eglBindAPI(EGL_OPENVG_API);
   vc->pbuff_surf = eglCreatePbufferSurface(vc->egl.dpy, vc->egl.config, pbufsurface_list);
   if (vc->pbuff_surf == EGL_NO_SURFACE)
   {
      RARCH_ERR("[VideoCore:EGLImage] failed to create PbufferSurface\n");
      goto fail;
   }

   vc->eglimage_ctx = eglCreateContext(vc->egl.dpy, vc->egl.config, NULL, NULL);
   if (vc->eglimage_ctx == EGL_NO_CONTEXT)
   {
      RARCH_ERR("[VideoCore:EGLImage] failed to create context\n");
      goto fail;
   }

   /* Test to make sure we can switch context. */
   result = eglMakeCurrent(vc->egl.dpy, vc->pbuff_surf, vc->pbuff_surf, vc->eglimage_ctx);
   if (result == EGL_FALSE)
   {
      RARCH_ERR("[VideoCore:EGLImage] failed to make context current\n");
      goto fail;
   }

   gfx_ctx_vc_bind_api(NULL, vc_api, 0, 0);
   eglMakeCurrent(vc->egl.dpy, vc->egl.surf, vc->egl.surf, vc->egl.ctx);

   vc->smooth = video->smooth;
   return true;

fail:
   if (vc->pbuff_surf != EGL_NO_SURFACE)
   {
      eglDestroySurface(vc->egl.dpy, vc->pbuff_surf);
      vc->pbuff_surf = EGL_NO_SURFACE;
   }

   if (vc->eglimage_ctx != EGL_NO_CONTEXT)
   {
      eglDestroyContext(vc->egl.dpy, vc->eglimage_ctx);
      vc->pbuff_surf = EGL_NO_CONTEXT;
   }

   gfx_ctx_vc_bind_api(NULL, vc_api, 0, 0);
   eglMakeCurrent(vc->egl.dpy, vc->egl.surf, vc->egl.surf, vc->egl.ctx);

   return false;
}