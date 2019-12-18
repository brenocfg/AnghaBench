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
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
#define  RARCH_SHADER_CG 133 
#define  RARCH_SHADER_GLSL 132 
#define  RARCH_SHADER_HLSL 131 
#define  RARCH_SHADER_METAL 130 
#define  RARCH_SHADER_NONE 129 
#define  RARCH_SHADER_SLANG 128 

const char *video_shader_to_str(enum rarch_shader_type type)
{
   switch (type)
   {
      case RARCH_SHADER_CG:
         return "Cg";
      case RARCH_SHADER_HLSL:
         return "HLSL";
      case RARCH_SHADER_GLSL:
         return "GLSL";
      case RARCH_SHADER_SLANG:
         return "Slang";
      case RARCH_SHADER_METAL:
         return "Metal";
      case RARCH_SHADER_NONE:
         return "none";
      default:
         break;
   }

   return "???";
}