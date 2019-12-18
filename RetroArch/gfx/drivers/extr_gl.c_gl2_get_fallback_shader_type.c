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
 int DEFAULT_SHADER_TYPE ; 
#define  RARCH_SHADER_CG 129 
#define  RARCH_SHADER_GLSL 128 
 int RARCH_SHADER_NONE ; 
 int /*<<< orphan*/  video_shader_is_supported (int) ; 

__attribute__((used)) static enum rarch_shader_type gl2_get_fallback_shader_type(enum rarch_shader_type type)
{
#if defined(HAVE_GLSL) || defined(HAVE_CG)
   unsigned i;

   if (type != RARCH_SHADER_CG && type != RARCH_SHADER_GLSL)
   {
      type = DEFAULT_SHADER_TYPE;

      if (type != RARCH_SHADER_CG && type != RARCH_SHADER_GLSL)
         type = RARCH_SHADER_GLSL;
   }

   for (i = 0; i < 2; i++)
   {
      switch (type)
      {
         case RARCH_SHADER_CG:
#ifdef HAVE_CG
            if (video_shader_is_supported(type))
               return type;
#endif
            type = RARCH_SHADER_GLSL;
            break;

         case RARCH_SHADER_GLSL:
#ifdef HAVE_GLSL
            if (video_shader_is_supported(type))
               return type;
#endif
            type = RARCH_SHADER_CG;
            break;

         default:
            return RARCH_SHADER_NONE;
      }
   }
#endif
   return RARCH_SHADER_NONE;
}