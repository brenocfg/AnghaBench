#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t server; } ;
struct TYPE_7__ {TYPE_2__* attrib; TYPE_1__ active_texture; } ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_3__ GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 size_t GL11_IX_COLOR ; 
 size_t GL11_IX_NORMAL ; 
 size_t GL11_IX_POINT_SIZE ; 
 size_t GL11_IX_TEXTURE_COORD ; 
 TYPE_3__* GLXX_GET_CLIENT_STATE (int /*<<< orphan*/ *) ; 
#define  GL_CURRENT_COLOR 131 
#define  GL_CURRENT_NORMAL 130 
#define  GL_CURRENT_TEXTURE_COORDS 129 
#define  GL_POINT_SIZE 128 
 size_t GL_TEXTURE0 ; 
 int /*<<< orphan*/  UNREACHABLE () ; 

__attribute__((used)) static int get_float_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLfloat *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   int i;

   switch (pname) {
   case GL_CURRENT_TEXTURE_COORDS:
   {
      /*
         apparently we need the current texture coordinates for the _server_ active texture unit
      */

      for (i = 0; i < 4; i++)
         params[i] = state->attrib[state->active_texture.server - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].value[i];
      return 4;
   }
   case GL_CURRENT_COLOR:
   {
      for (i = 0; i < 4; i++)
         params[i] = state->attrib[GL11_IX_COLOR].value[i];
      return 4;
   }
   case GL_CURRENT_NORMAL:
   {
      for (i = 0; i < 3; i++)
         params[i] = state->attrib[GL11_IX_NORMAL].value[i];
      return 3;
   }
   case GL_POINT_SIZE:
      params[0] = state->attrib[GL11_IX_POINT_SIZE].value[0];
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}