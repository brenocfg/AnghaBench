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
struct TYPE_2__ {unsigned int width; unsigned int height; int /*<<< orphan*/  native_window; int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ vivante_ctx_data_t ;
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_CONTEXT_CLIENT_VERSION 129 
#define  EGL_NONE 128 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  egl_create_context (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  egl_create_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  fbCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbGetDisplayByIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_ctx_vivante_destroy (void*) ; 

__attribute__((used)) static bool gfx_ctx_vivante_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
#ifdef HAVE_EGL
   static const EGLint attribs[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2, /* Use version 2, even for GLES3. */
      EGL_NONE
   };
#endif
   vivante_ctx_data_t *viv = (vivante_ctx_data_t*)data;

   /* Pick some arbitrary default. */
   if (!width || !fullscreen)
      width = 1280;
   if (!height || !fullscreen)
      height = 1024;

   viv->width    = width;
   viv->height   = height;

#ifdef HAVE_EGL
   if (!egl_create_context(&viv->egl, attribs))
   {
      egl_report_error();
      goto error;
   }
#endif

   viv->native_window = fbCreateWindow(fbGetDisplayByIndex(0), 0, 0, 0, 0);

#ifdef HAVE_EGL
   if (!egl_create_surface(&viv->egl, viv->native_window))
      goto error;
#endif

   return true;

error:
   RARCH_ERR("[Vivante fbdev]: EGL error: %d.\n", eglGetError());
   gfx_ctx_vivante_destroy(data);
   return false;
}