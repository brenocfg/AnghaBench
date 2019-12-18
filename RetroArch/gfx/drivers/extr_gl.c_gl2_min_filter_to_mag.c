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
 int GL_LINEAR ; 
#define  GL_LINEAR_MIPMAP_LINEAR 129 
 int GL_NEAREST ; 
#define  GL_NEAREST_MIPMAP_NEAREST 128 

__attribute__((used)) static GLenum gl2_min_filter_to_mag(GLenum type)
{
   switch (type)
   {
      case GL_LINEAR_MIPMAP_LINEAR:
         return GL_LINEAR;
      case GL_NEAREST_MIPMAP_NEAREST:
         return GL_NEAREST;
      default:
         break;
   }

   return type;
}