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
 int GL_CLAMP_TO_BORDER ; 
 int GL_CLAMP_TO_EDGE ; 
 int GL_MIRRORED_REPEAT ; 
 int GL_REPEAT ; 
#define  RARCH_WRAP_BORDER 131 
#define  RARCH_WRAP_EDGE 130 
#define  RARCH_WRAP_MIRRORED_REPEAT 129 
#define  RARCH_WRAP_REPEAT 128 

__attribute__((used)) static unsigned gl2_wrap_type_to_enum(enum gfx_wrap_type type)
{
   switch (type)
   {
#ifndef HAVE_OPENGLES
      case RARCH_WRAP_BORDER: /* GL_CLAMP_TO_BORDER: Available since GL 1.3 */
         return GL_CLAMP_TO_BORDER;
#else
      case RARCH_WRAP_BORDER:
#endif
      case RARCH_WRAP_EDGE:
         return GL_CLAMP_TO_EDGE;
      case RARCH_WRAP_REPEAT:
         return GL_REPEAT;
      case RARCH_WRAP_MIRRORED_REPEAT:
         return GL_MIRRORED_REPEAT;
      default:
	 break;
   }

   return 0;
}