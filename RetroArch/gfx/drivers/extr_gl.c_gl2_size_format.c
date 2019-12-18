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
typedef  int GLint ;

/* Variables and functions */
#define  GL_RGB 129 
 int GL_RGB565 ; 
#define  GL_RGBA 128 
 int GL_RGBA8 ; 
 int GL_RGBA8_OES ; 

__attribute__((used)) static void gl2_size_format(GLint* internalFormat)
{
#ifndef HAVE_PSGL
   switch (*internalFormat)
   {
      case GL_RGB:
         /* FIXME: PS3 does not support this, neither does it have GL_RGB565_OES. */
         *internalFormat = GL_RGB565;
         break;
      case GL_RGBA:
#ifdef HAVE_OPENGLES2
         *internalFormat = GL_RGBA8_OES;
#else
         *internalFormat = GL_RGBA8;
#endif
         break;
   }
#endif
}