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
struct video_coords {int vertices; int /*<<< orphan*/  lut_tex_coord; int /*<<< orphan*/  color; int /*<<< orphan*/  vertex; int /*<<< orphan*/  tex_coord; } ;
struct shader_uniforms {scalar_t__ color; scalar_t__ tex_coord; scalar_t__ vertex_coord; scalar_t__ lut_tex_coord; } ;
struct glsl_attrib {int dummy; } ;
struct TYPE_7__ {size_t active_idx; TYPE_2__* vbo; TYPE_1__* shader; struct shader_uniforms* uniforms; } ;
typedef  TYPE_3__ glsl_shader_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  size_primary; int /*<<< orphan*/  buffer_primary; int /*<<< orphan*/  vbo_primary; } ;
struct TYPE_5__ {int /*<<< orphan*/  modern; } ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_glsl_set_attribs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,struct glsl_attrib*,size_t) ; 
 int /*<<< orphan*/  gl_glsl_set_coord_array (struct glsl_attrib*,scalar_t__,int /*<<< orphan*/ ,struct video_coords const*,size_t,int) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static bool gl_glsl_set_coords(void *shader_data,
      const struct video_coords *coords)
{
   GLfloat short_buffer[4 * (2 + 2 + 4 + 2)];
   struct glsl_attrib attribs[4];
   size_t               attribs_size = 0;
   size_t                       size = 0;
   GLfloat *buffer                   = short_buffer;
   glsl_shader_data_t          *glsl = (glsl_shader_data_t*)shader_data;
   const struct shader_uniforms *uni = glsl
      ? &glsl->uniforms[glsl->active_idx] : NULL;

   if (!glsl || !glsl->shader->modern || !coords)
   {
      if (coords)
         return false;
      return true;
   }

   if (coords->vertices > 4)
   {
      /* Avoid hitting malloc on every single regular quad draw. */

      size_t elems  = 0;
      elems        += (uni->color >= 0)         * 4;
      elems        += (uni->tex_coord >= 0)     * 2;
      elems        += (uni->vertex_coord >= 0)  * 2;
      elems        += (uni->lut_tex_coord >= 0) * 2;

      elems        *= coords->vertices * sizeof(GLfloat);

      buffer        = (GLfloat*)malloc(elems);
   }

   if (!buffer)
      return false;

   if (uni->tex_coord >= 0)
   {
      gl_glsl_set_coord_array(attribs, uni->tex_coord,
            coords->tex_coord, coords, size, 2);
      attribs_size++;
   }

   if (uni->vertex_coord >= 0)
   {
      gl_glsl_set_coord_array(attribs, uni->vertex_coord,
            coords->vertex, coords, size, 2);
      attribs_size++;
   }

   if (uni->color >= 0)
   {
      gl_glsl_set_coord_array(attribs, uni->color,
            coords->color, coords, size, 4);
      attribs_size++;
   }

   if (uni->lut_tex_coord >= 0)
   {
      gl_glsl_set_coord_array(attribs, uni->lut_tex_coord,
            coords->lut_tex_coord, coords, size, 2);
      attribs_size++;
   }

   if (size)
      gl_glsl_set_attribs(glsl,
            glsl->vbo[glsl->active_idx].vbo_primary,
            &glsl->vbo[glsl->active_idx].buffer_primary,
            &glsl->vbo[glsl->active_idx].size_primary,
            buffer, size,
            attribs, attribs_size);

   if (buffer != short_buffer)
      free(buffer);

   return true;
}