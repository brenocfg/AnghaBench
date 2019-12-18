#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_16__ {int vertices; int /*<<< orphan*/  color; int /*<<< orphan*/  tex_coord; int /*<<< orphan*/  vertex; } ;
typedef  TYPE_5__ video_coords_t ;
struct TYPE_17__ {TYPE_10__* gl; int /*<<< orphan*/  tex; TYPE_1__* atlas; } ;
typedef  TYPE_6__ gl_core_raster_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {scalar_t__ flat_ubo_vertex; } ;
struct TYPE_14__ {TYPE_2__ font_loc; } ;
struct TYPE_12__ {int dirty; } ;
struct TYPE_11__ {TYPE_4__ mvp_no_rot; TYPE_3__ pipelines; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE1 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glUniform4fv (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  gl_core_bind_scratch_vbo (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_core_raster_font_upload_atlas (TYPE_6__*) ; 

__attribute__((used)) static void gl_core_raster_font_draw_vertices(gl_core_raster_t *font,
      const video_coords_t *coords,
      video_frame_info_t *video_info)
{
   if (font->atlas->dirty)
   {
      gl_core_raster_font_upload_atlas(font);
      font->atlas->dirty   = false;
   }

   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, font->tex);

   if (font->gl->pipelines.font_loc.flat_ubo_vertex >= 0)
   {
      glUniform4fv(font->gl->pipelines.font_loc.flat_ubo_vertex,
                   4, font->gl->mvp_no_rot.data);
   }

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   gl_core_bind_scratch_vbo(font->gl, coords->vertex, 2 * sizeof(float) * coords->vertices);
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(uintptr_t)0);

   gl_core_bind_scratch_vbo(font->gl, coords->tex_coord, 2 * sizeof(float) * coords->vertices);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(uintptr_t)0);

   gl_core_bind_scratch_vbo(font->gl, coords->color, 4 * sizeof(float) * coords->vertices);
   glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(uintptr_t)0);

   glDrawArrays(GL_TRIANGLES, 0, coords->vertices);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}