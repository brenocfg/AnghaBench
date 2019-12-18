#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int major; int /*<<< orphan*/  minor; } ;
struct TYPE_5__ {TYPE_1__ egl; } ;
typedef  TYPE_2__ xegl_ctx_data_t ;
struct retro_hw_render_callback {int debug_context; } ;
typedef  int EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_CONTEXT_CLIENT_VERSION ; 
 int /*<<< orphan*/  EGL_CONTEXT_FLAGS_KHR ; 
 int /*<<< orphan*/  EGL_CONTEXT_MAJOR_VERSION_KHR ; 
 void* EGL_CONTEXT_MINOR_VERSION_KHR ; 
 int /*<<< orphan*/  EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR ; 
 int /*<<< orphan*/  EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR ; 
 int /*<<< orphan*/  EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR ; 
 int EGL_NONE ; 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_OPENGL_ES_API 128 
 struct retro_hw_render_callback* video_driver_get_hw_context () ; 
 int xegl_api ; 

__attribute__((used)) static EGLint *xegl_fill_attribs(xegl_ctx_data_t *xegl, EGLint *attr)
{
   switch (xegl_api)
   {
#ifdef EGL_KHR_create_context
      case GFX_CTX_OPENGL_API:
         {
            unsigned version = xegl->egl.major * 1000 + xegl->egl.minor;
            bool core        = version >= 3001;
#ifdef GL_DEBUG
            bool debug       = true;
#else
            struct retro_hw_render_callback *hwr = video_driver_get_hw_context();
            bool debug       = hwr->debug_context;
#endif

            if (core)
            {
               *attr++ = EGL_CONTEXT_MAJOR_VERSION_KHR;
               *attr++ = xegl->egl.major;
               *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
               *attr++ = xegl->egl.minor;

               /* Technically, we don't have core/compat until 3.2.
                * Version 3.1 is either compat or not depending
                * on GL_ARB_compatibility.
                */
               if (version >= 3002)
               {
                  *attr++ = EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR;
                  *attr++ = EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR;
               }
            }

            if (debug)
            {
               *attr++ = EGL_CONTEXT_FLAGS_KHR;
               *attr++ = EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR;
            }

            break;
         }
#endif

      case GFX_CTX_OPENGL_ES_API:
         /* Same as EGL_CONTEXT_MAJOR_VERSION. */
         *attr++ = EGL_CONTEXT_CLIENT_VERSION;
         *attr++ = xegl->egl.major ? (EGLint)xegl->egl.major : 2;
#ifdef EGL_KHR_create_context
         if (xegl->egl.minor > 0)
         {
            *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
            *attr++ = xegl->egl.minor;
         }
#endif
         break;

      default:
         break;
   }

   *attr = EGL_NONE;
   return attr;
}