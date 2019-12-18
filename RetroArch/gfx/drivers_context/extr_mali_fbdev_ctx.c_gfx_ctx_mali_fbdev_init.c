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
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  void mali_ctx_data_t ;
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_ALPHA_SIZE 136 
#define  EGL_BLUE_SIZE 135 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
#define  EGL_GREEN_SIZE 134 
#define  EGL_NONE 133 
#define  EGL_OPENGL_ES2_BIT 132 
#define  EGL_RED_SIZE 131 
#define  EGL_RENDERABLE_TYPE 130 
#define  EGL_SURFACE_TYPE 129 
#define  EGL_WINDOW_BIT 128 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  egl_init_context (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int*,int*,int*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  frontend_driver_install_signal_handler () ; 
 int /*<<< orphan*/  gfx_ctx_mali_fbdev_destroy (void*) ; 

__attribute__((used)) static void *gfx_ctx_mali_fbdev_init(video_frame_info_t *video_info,
      void *video_driver)
{
#ifdef HAVE_EGL
   EGLint n;
   EGLint major, minor;
   EGLint format;
   static const EGLint attribs[] = {
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_RED_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_NONE
   };
#endif

   mali_ctx_data_t *mali = (mali_ctx_data_t*)calloc(1, sizeof(*mali));

   if (!mali)
       return NULL;

#ifdef HAVE_EGL
   frontend_driver_install_signal_handler();
#endif

#ifdef HAVE_EGL
   if (!egl_init_context(&mali->egl, EGL_NONE, EGL_DEFAULT_DISPLAY,
            &major, &minor, &n, attribs, NULL))
   {
      egl_report_error();
      goto error;
   }
#endif

   return mali;

error:
   RARCH_ERR("[Mali fbdev]: EGL error: %d.\n", eglGetError());
   gfx_ctx_mali_fbdev_destroy(video_driver);
   return NULL;
}