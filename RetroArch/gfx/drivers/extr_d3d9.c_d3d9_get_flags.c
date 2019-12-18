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
 int /*<<< orphan*/  GFX_CTX_FLAGS_BLACK_FRAME_INSERTION ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_MENU_FRAME_FILTERING ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_CG ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_SHADERS_HLSL ; 
 scalar_t__ RARCH_SHADER_CG ; 
 scalar_t__ RARCH_SHADER_HLSL ; 
 scalar_t__ supported_shader_type ; 

__attribute__((used)) static uint32_t d3d9_get_flags(void *data)
{
   uint32_t flags = 0;

   BIT32_SET(flags, GFX_CTX_FLAGS_BLACK_FRAME_INSERTION);
   BIT32_SET(flags, GFX_CTX_FLAGS_MENU_FRAME_FILTERING);

   if (supported_shader_type == RARCH_SHADER_CG)
      BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_CG);
   else if (supported_shader_type == RARCH_SHADER_HLSL)
      BIT32_SET(flags, GFX_CTX_FLAGS_SHADERS_HLSL);

   return flags;
}