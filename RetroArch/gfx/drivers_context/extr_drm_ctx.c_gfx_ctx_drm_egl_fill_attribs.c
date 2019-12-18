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
struct retro_hw_render_callback {int debug_context; } ;
struct TYPE_4__ {int major; int /*<<< orphan*/  minor; } ;
struct TYPE_5__ {TYPE_1__ egl; } ;
typedef  TYPE_2__ gfx_ctx_drm_data_t ;
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
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_OPENGL_ES_API 128 
 int drm_api ; 
 struct retro_hw_render_callback* video_driver_get_hw_context () ; 

__attribute__((used)) static EGLint *gfx_ctx_drm_egl_fill_attribs(
      gfx_ctx_drm_data_t *drm, EGLint *attr)
{
   switch (drm_api)
   {
#ifdef EGL_KHR_create_context
      case GFX_CTX_OPENGL_API:
      {
         bool debug       = false;
#ifdef HAVE_OPENGL
         unsigned version = drm->egl.major * 1000 + drm->egl.minor;
         bool core        = version >= 3001;
#ifdef GL_DEBUG
         debug            = true;
#else
         struct retro_hw_render_callback *hwr = video_driver_get_hw_context();
         debug           = hwr->debug_context;
#endif

         if (core)
         {
            *attr++ = EGL_CONTEXT_MAJOR_VERSION_KHR;
            *attr++ = drm->egl.major;
            *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
            *attr++ = drm->egl.minor;

            /* Technically, we don't have core/compat until 3.2.
             * Version 3.1 is either compat or not depending
             * on GL_ARB_compatibility. */
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
#endif
      }
#endif

      case GFX_CTX_OPENGL_ES_API:
#ifdef HAVE_OPENGLES
         *attr++ = EGL_CONTEXT_CLIENT_VERSION;
         *attr++ = drm->egl.major
            ? (EGLint)drm->egl.major : 2;
#ifdef EGL_KHR_create_context
         if (drm->egl.minor > 0)
         {
            *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
            *attr++ = drm->egl.minor;
         }
#endif
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   *attr = EGL_NONE;
   return attr;
}