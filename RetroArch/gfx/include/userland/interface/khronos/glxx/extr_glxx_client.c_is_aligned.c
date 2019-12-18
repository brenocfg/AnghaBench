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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_BYTE 133 
 int GL_FALSE ; 
#define  GL_FIXED 132 
#define  GL_FLOAT 131 
#define  GL_SHORT 130 
 int GL_TRUE ; 
#define  GL_UNSIGNED_BYTE 129 
#define  GL_UNSIGNED_SHORT 128 
 int /*<<< orphan*/  UNREACHABLE () ; 

__attribute__((used)) static bool is_aligned( GLenum type, size_t value)
{
   switch (type) {
   case GL_BYTE:
   case GL_UNSIGNED_BYTE:
      return GL_TRUE;
   case GL_SHORT:
   case GL_UNSIGNED_SHORT:
      return (value & 1) == 0;
   case GL_FIXED:
   case GL_FLOAT:
      return (value & 3) == 0;
   default:
      UNREACHABLE();
      return GL_FALSE;
   }
}