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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  g_core_es; int /*<<< orphan*/  core_hw_context_enable; } ;
typedef  TYPE_1__ gfx_ctx_x_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_ADAPTIVE_VSYNC ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_MULTISAMPLING ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_CG ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_GLSL ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_SLANG ; 
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_driver_get_ident () ; 
 int /*<<< orphan*/  x_adaptive_vsync ; 
 int x_api ; 
 int /*<<< orphan*/  x_enable_msaa ; 

__attribute__((used)) static uint32_t gfx_ctx_x_get_flags(void *data)
{
   uint32_t      flags = 0;
   gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;

   switch (x_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
         if (x_adaptive_vsync)
            BIT32_SET(flags, GFX_CTX_FLAGS_ADAPTIVE_VSYNC);

         if (x->core_hw_context_enable || x->g_core_es)
            BIT32_SET(flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT);

         if (x_enable_msaa)
            BIT32_SET(flags, GFX_CTX_FLAGS_MULTISAMPLING);

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
            if (!(x->core_hw_context_enable || x->g_core_es))
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