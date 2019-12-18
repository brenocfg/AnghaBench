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
typedef  enum gfx_wrap_type { ____Placeholder_gfx_wrap_type } gfx_wrap_type ;

/* Variables and functions */
 int GL_CLAMP ; 
 int GL_REPEAT ; 
#define  RARCH_WRAP_MIRRORED_REPEAT 129 
#define  RARCH_WRAP_REPEAT 128 

__attribute__((used)) static unsigned gl1_wrap_type_to_enum(enum gfx_wrap_type type)
{
   switch (type)
   {
      case RARCH_WRAP_REPEAT:
      case RARCH_WRAP_MIRRORED_REPEAT: /* mirrored not actually supported */
         return GL_REPEAT;
      default:
         return GL_CLAMP;
   }

   return 0;
}