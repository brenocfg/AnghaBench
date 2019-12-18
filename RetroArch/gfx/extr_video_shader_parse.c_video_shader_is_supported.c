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
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
typedef  enum display_flags { ____Placeholder_display_flags } display_flags ;

/* Variables and functions */
 int BIT32_GET (scalar_t__,int) ; 
 int GFX_CTX_FLAGS_NONE ; 
 int GFX_CTX_FLAGS_SHADERS_CG ; 
 int GFX_CTX_FLAGS_SHADERS_GLSL ; 
 int GFX_CTX_FLAGS_SHADERS_HLSL ; 
 int GFX_CTX_FLAGS_SHADERS_SLANG ; 
#define  RARCH_SHADER_CG 132 
#define  RARCH_SHADER_GLSL 131 
#define  RARCH_SHADER_HLSL 130 
#define  RARCH_SHADER_NONE 129 
#define  RARCH_SHADER_SLANG 128 
 int /*<<< orphan*/  video_context_driver_get_flags (TYPE_1__*) ; 

bool video_shader_is_supported(enum rarch_shader_type type)
{
   gfx_ctx_flags_t flags;
   enum display_flags testflag = GFX_CTX_FLAGS_NONE;

   flags.flags     = 0;

   switch (type)
   {
      case RARCH_SHADER_SLANG:
         testflag = GFX_CTX_FLAGS_SHADERS_SLANG;
         break;
      case RARCH_SHADER_GLSL:
         testflag = GFX_CTX_FLAGS_SHADERS_GLSL;
         break;
      case RARCH_SHADER_CG:
         testflag = GFX_CTX_FLAGS_SHADERS_CG;
         break;
      case RARCH_SHADER_HLSL:
         testflag = GFX_CTX_FLAGS_SHADERS_HLSL;
         break;
      case RARCH_SHADER_NONE:
      default:
         return false;
   }
   video_context_driver_get_flags(&flags);

   return BIT32_GET(flags.flags, testflag);
}