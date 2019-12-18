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
struct TYPE_5__ {size_t client; } ;
struct TYPE_7__ {TYPE_2__* attrib; TYPE_1__ active_texture; } ;
struct TYPE_6__ {int /*<<< orphan*/  enabled; } ;
typedef  int GLenum ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_3__ GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 size_t GL11_IX_COLOR ; 
 size_t GL11_IX_MATRIX_INDEX ; 
 size_t GL11_IX_MATRIX_WEIGHT ; 
 size_t GL11_IX_NORMAL ; 
 size_t GL11_IX_POINT_SIZE ; 
 size_t GL11_IX_TEXTURE_COORD ; 
 size_t GL11_IX_VERTEX ; 
 TYPE_3__* GLXX_GET_CLIENT_STATE (int /*<<< orphan*/ *) ; 
#define  GL_COLOR_ARRAY 134 
#define  GL_MATRIX_INDEX_ARRAY_OES 133 
#define  GL_NORMAL_ARRAY 132 
#define  GL_POINT_SIZE_ARRAY_OES 131 
 size_t GL_TEXTURE0 ; 
#define  GL_TEXTURE_COORD_ARRAY 130 
#define  GL_VERTEX_ARRAY 129 
#define  GL_WEIGHT_ARRAY_OES 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_boolean_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLboolean *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_VERTEX_ARRAY:
      params[0] = state->attrib[GL11_IX_VERTEX].enabled;
      return 1;
   case GL_NORMAL_ARRAY:
      params[0] = state->attrib[GL11_IX_NORMAL].enabled;
      return 1;
   case GL_COLOR_ARRAY:
      params[0] = state->attrib[GL11_IX_COLOR].enabled;
      return 1;
   case GL_TEXTURE_COORD_ARRAY:
      params[0] = state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].enabled;
      return 1;
   case GL_POINT_SIZE_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_POINT_SIZE].enabled;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_MATRIX_INDEX].enabled;
      return 1;
   case GL_WEIGHT_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_MATRIX_WEIGHT].enabled;
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}