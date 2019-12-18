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
struct TYPE_3__ {scalar_t__ flags; } ;
typedef  TYPE_1__ gfx_ctx_flags_t ;

/* Variables and functions */
 scalar_t__ BIT32_GET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_CG ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_GLSL ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_HLSL ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_SLANG ; 
 int /*<<< orphan*/  video_context_driver_get_flags (TYPE_1__*) ; 

bool video_shader_any_supported(void)
{
   gfx_ctx_flags_t flags;
   flags.flags     = 0;
   video_context_driver_get_flags(&flags);

   return
      BIT32_GET(flags.flags, GFX_CTX_FLAGS_SHADERS_SLANG) ||
      BIT32_GET(flags.flags, GFX_CTX_FLAGS_SHADERS_GLSL)  ||
      BIT32_GET(flags.flags, GFX_CTX_FLAGS_SHADERS_CG)    ||
      BIT32_GET(flags.flags, GFX_CTX_FLAGS_SHADERS_HLSL);
}