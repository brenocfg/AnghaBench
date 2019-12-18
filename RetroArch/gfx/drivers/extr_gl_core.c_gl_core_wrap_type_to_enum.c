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

__attribute__((used)) static unsigned gl_core_wrap_type_to_enum(enum gfx_wrap_type type)
{
   switch (type)
   {
      case RARCH_WRAP_BORDER:
#ifdef HAVE_OPENGLES3
         /* GLES does not support CLAMP_TO_BORDER until GLES 3.2.
          * It is a deprecated feature in general. */
         return GL_CLAMP_TO_EDGE;
#else
         return GL_CLAMP_TO_BORDER;
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