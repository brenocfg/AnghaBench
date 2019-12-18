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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
#define  GL_BYTE 134 
#define  GL_FIXED 133 
#define  GL_FLOAT 132 
#define  GL_HALF_FLOAT_OES 131 
#define  GL_SHORT 130 
#define  GL_UNSIGNED_BYTE 129 
#define  GL_UNSIGNED_SHORT 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

int khrn_get_type_size(int type)
{
   switch ((GLenum)type) {
   case GL_BYTE:
   case GL_UNSIGNED_BYTE:
      return 1;
   case GL_SHORT:
   case GL_UNSIGNED_SHORT:
   case GL_HALF_FLOAT_OES:
      return 2;
   case GL_FIXED:
   case GL_FLOAT:
      return 4;
   default:
      UNREACHABLE();
      return 0;
   }
}