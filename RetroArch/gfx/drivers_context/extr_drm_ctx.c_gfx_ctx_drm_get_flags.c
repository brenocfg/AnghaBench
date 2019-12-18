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
struct TYPE_2__ {scalar_t__ core_hw_context_enable; } ;
typedef  TYPE_1__ gfx_ctx_drm_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_CUSTOMIZABLE_SWAPCHAIN_IMAGES ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_GLSL ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_SLANG ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_driver_get_ident () ; 

__attribute__((used)) static uint32_t gfx_ctx_drm_get_flags(void *data)
{
   uint32_t             flags = 0;
   gfx_ctx_drm_data_t    *drm = (gfx_ctx_drm_data_t*)data;

   BIT32_SET(flags, GFX_CTX_FLAGS_CUSTOMIZABLE_SWAPCHAIN_IMAGES);

   if (drm->core_hw_context_enable)
      BIT32_SET(flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT);

   if (string_is_equal(video_driver_get_ident(), "glcore"))
   {
#if defined(HAVE_SLANG) && defined(HAVE_SPIRV_CROSS)
      BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_SLANG);
#endif
   }
   else
      BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_GLSL);

   return flags;
}