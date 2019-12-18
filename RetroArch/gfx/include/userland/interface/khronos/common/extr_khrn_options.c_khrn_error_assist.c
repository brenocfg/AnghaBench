#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ gl_error_assist; } ;
typedef  int GLenum ;

/* Variables and functions */
#define  GL_INVALID_ENUM 131 
#define  GL_INVALID_OPERATION 130 
#define  GL_INVALID_VALUE 129 
 int GL_NO_ERROR ; 
#define  GL_OUT_OF_MEMORY 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ khrn_options ; 
 int /*<<< orphan*/  stderr ; 

void khrn_error_assist(GLenum error, const char *func)
{
   if (khrn_options.gl_error_assist && error != GL_NO_ERROR)
   {
      fprintf(stderr, "V3D ERROR ASSIST : ");
      switch (error)
      {
      case GL_INVALID_ENUM      : fprintf(stderr, "GL_INVALID_ENUM in %s\n", func); break;
      case GL_INVALID_VALUE     : fprintf(stderr, "GL_INVALID_VALUE in %s\n", func); break;
      case GL_INVALID_OPERATION : fprintf(stderr, "GL_INVALID_OPERATION in %s\n", func); break;
      case GL_OUT_OF_MEMORY     : fprintf(stderr, "GL_OUT_OF_MEMORY in %s\n", func); break;
      default                   : fprintf(stderr, "ERROR CODE %d in %s\n", (int)error, func); break;
      }
      fflush(stderr);
   }
}