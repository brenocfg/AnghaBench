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
#define  GL_INVALID_ENUM 136 
#define  GL_INVALID_FRAMEBUFFER_OPERATION 135 
#define  GL_INVALID_OPERATION 134 
#define  GL_INVALID_VALUE 133 
#define  GL_OUT_OF_MEMORY 132 
#define  GL_STACK_OVERFLOW 131 
#define  GL_STACK_UNDERFLOW 130 
#define  GL_TABLE_TOO_LARGE 129 
#define  GL_TEXTURE_TOO_LARGE 128 

__attribute__((used)) static const char* fghErrorString( GLenum error )
{
  switch ( error ) {
  case GL_INVALID_ENUM: return "invalid enumerant";
  case GL_INVALID_VALUE: return "invalid value";
  case GL_INVALID_OPERATION: return "invalid operation";
  case GL_STACK_OVERFLOW: return "stack overflow";
  case GL_STACK_UNDERFLOW: return "stack underflow";
  case GL_OUT_OF_MEMORY: return "out of memory";
  case GL_TABLE_TOO_LARGE: return "table too large";
  case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
  case GL_TEXTURE_TOO_LARGE: return "texture too large";
  default: return "unknown GL error";
  }
}