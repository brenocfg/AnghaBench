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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_ADAPTIVE_VSYNC ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_CG ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_GLSL ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_SLANG ; 
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_driver_get_ident () ; 
 int /*<<< orphan*/  wgl_adaptive_vsync ; 
 int win32_api ; 
 int /*<<< orphan*/  win32_core_hw_context_enable ; 

__attribute__((used)) static uint32_t gfx_ctx_wgl_get_flags(void *data)
{
   uint32_t flags = 0;

   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
         if (wgl_adaptive_vsync)
            BIT32_SET(flags, GFX_CTX_FLAGS_ADAPTIVE_VSYNC);

         if (win32_core_hw_context_enable)
            BIT32_SET(flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT);

         if (string_is_equal(video_driver_get_ident(), "gl1")) { }
         else if (string_is_equal(video_driver_get_ident(), "glcore"))
         {
#if defined(HAVE_SLANG) && defined(HAVE_SPIRV_CROSS)
            BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_SLANG);
#endif
         }
         else
         {
#ifdef HAVE_CG
            if (!win32_core_hw_context_enable)
               BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_CG);
#endif
#ifdef HAVE_GLSL
            BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_GLSL);
#endif
         }

         break;
      case GFX_CTX_VULKAN_API:
#if defined(HAVE_SLANG) && defined(HAVE_SPIRV_CROSS)
         BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_SLANG);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   return flags;
}