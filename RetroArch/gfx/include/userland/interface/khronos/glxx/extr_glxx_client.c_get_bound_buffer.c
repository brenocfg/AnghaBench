#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  element_array; int /*<<< orphan*/  array; } ;
struct TYPE_5__ {TYPE_1__ bound_buffer; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLenum ;
typedef  TYPE_2__ GLXX_CLIENT_STATE_T ;

/* Variables and functions */
#define  GL_ARRAY_BUFFER 129 
#define  GL_ELEMENT_ARRAY_BUFFER 128 

__attribute__((used)) static GLuint get_bound_buffer(GLXX_CLIENT_STATE_T *state, GLenum target)
{
   GLuint buffer = 0;

   switch (target) {
   case GL_ARRAY_BUFFER:
      buffer = state->bound_buffer.array;
      break;
   case GL_ELEMENT_ARRAY_BUFFER:
      buffer = state->bound_buffer.element_array;
      break;
   default:
      break;
   }
   return buffer;
}