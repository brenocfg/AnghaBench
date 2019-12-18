#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pack; int /*<<< orphan*/  unpack; } ;
struct TYPE_8__ {size_t client; } ;
struct TYPE_9__ {int /*<<< orphan*/  element_array; int /*<<< orphan*/  array; } ;
struct TYPE_11__ {TYPE_1__ alignment; TYPE_4__* attrib; TYPE_2__ active_texture; TYPE_3__ bound_buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  stride; int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int GLenum ;
typedef  TYPE_5__ GLXX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 size_t GL11_IX_COLOR ; 
 size_t GL11_IX_MATRIX_INDEX ; 
 size_t GL11_IX_MATRIX_WEIGHT ; 
 size_t GL11_IX_NORMAL ; 
 size_t GL11_IX_POINT_SIZE ; 
 size_t GL11_IX_TEXTURE_COORD ; 
 size_t GL11_IX_VERTEX ; 
 TYPE_5__* GLXX_GET_CLIENT_STATE (int /*<<< orphan*/ *) ; 
#define  GL_ARRAY_BUFFER_BINDING 160 
#define  GL_CLIENT_ACTIVE_TEXTURE 159 
#define  GL_COLOR_ARRAY_BUFFER_BINDING 158 
#define  GL_COLOR_ARRAY_SIZE 157 
#define  GL_COLOR_ARRAY_STRIDE 156 
#define  GL_COLOR_ARRAY_TYPE 155 
#define  GL_ELEMENT_ARRAY_BUFFER_BINDING 154 
#define  GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 153 
#define  GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 152 
#define  GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 151 
#define  GL_MATRIX_INDEX_ARRAY_SIZE_OES 150 
#define  GL_MATRIX_INDEX_ARRAY_STRIDE_OES 149 
#define  GL_MATRIX_INDEX_ARRAY_TYPE_OES 148 
#define  GL_NORMAL_ARRAY_BUFFER_BINDING 147 
#define  GL_NORMAL_ARRAY_STRIDE 146 
#define  GL_NORMAL_ARRAY_TYPE 145 
#define  GL_PACK_ALIGNMENT 144 
#define  GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES 143 
#define  GL_POINT_SIZE_ARRAY_STRIDE_OES 142 
#define  GL_POINT_SIZE_ARRAY_TYPE_OES 141 
 int /*<<< orphan*/  GL_RGBA ; 
 size_t GL_TEXTURE0 ; 
#define  GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 140 
#define  GL_TEXTURE_COORD_ARRAY_SIZE 139 
#define  GL_TEXTURE_COORD_ARRAY_STRIDE 138 
#define  GL_TEXTURE_COORD_ARRAY_TYPE 137 
#define  GL_UNPACK_ALIGNMENT 136 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
#define  GL_VERTEX_ARRAY_BUFFER_BINDING 135 
#define  GL_VERTEX_ARRAY_SIZE 134 
#define  GL_VERTEX_ARRAY_STRIDE 133 
#define  GL_VERTEX_ARRAY_TYPE 132 
#define  GL_WEIGHT_ARRAY_BUFFER_BINDING_OES 131 
#define  GL_WEIGHT_ARRAY_SIZE_OES 130 
#define  GL_WEIGHT_ARRAY_STRIDE_OES 129 
#define  GL_WEIGHT_ARRAY_TYPE_OES 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_integer_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLint *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_CLIENT_ACTIVE_TEXTURE:
      params[0] = (GLint) state->active_texture.client;
      return 1;
   case GL_VERTEX_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].size;
      return 1;
   case GL_VERTEX_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].type;
      return 1;
   case GL_VERTEX_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].stride;
      return 1;
   case GL_NORMAL_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].type;
      return 1;
   case GL_NORMAL_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].stride;
      return 1;
   case GL_COLOR_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].size;
      return 1;
   case GL_COLOR_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].type;
      return 1;
   case GL_COLOR_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].stride;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].size;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].type;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].stride;
      return 1;
   case GL_POINT_SIZE_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].type;
      return 1;
   case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].stride;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_SIZE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].size;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].type;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].stride;
      return 1;
   case GL_WEIGHT_ARRAY_SIZE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].size;
      return 1;
   case GL_WEIGHT_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].type;
      return 1;
   case GL_WEIGHT_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].stride;
      return 1;
   case GL_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->bound_buffer.array;
      return 1;
   case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->bound_buffer.element_array;
      return 1;
   case GL_VERTEX_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].buffer;
      return 1;
   case GL_NORMAL_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].buffer;
      return 1;
   case GL_COLOR_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].buffer;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      /*
      TODO is this right?
      Most texture state variables are qualified by the value of ACTIVE TEXTURE
to determine which server texture state vector is queried. Client texture
state variables such as texture coordinate array pointers are qualified by the
value of CLIENT ACTIVE TEXTURE. Tables 6.3, 6.4, 6.7, 6.13, 6.15, and 6.21
indicate those state variables which are qualified by ACTIVE TEXTURE or
CLIENT ACTIVE TEXTURE during state queries
      */
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].buffer;
      return 1;
   case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].buffer;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].buffer;
      return 1;
   case GL_WEIGHT_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].buffer;
      return 1;

   case GL_UNPACK_ALIGNMENT:
      params[0] = (GLint) state->alignment.unpack;
      return 1;
   case GL_PACK_ALIGNMENT:
      params[0] = (GLint) state->alignment.pack;
      return 1;

   //TODO: these are horrible and don't make any sense
   //Is this a sensible thing to return?
   case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      params[0] = (GLint) GL_UNSIGNED_BYTE;
      return 1;
   case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
      params[0] = (GLint) GL_RGBA;
      return 1;
   //end TODO

   default:
      UNREACHABLE();
      break;
   }

   return 0;
}