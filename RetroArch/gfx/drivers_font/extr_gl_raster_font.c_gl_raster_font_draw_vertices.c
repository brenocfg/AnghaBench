#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  vertices; } ;
typedef  TYPE_4__ video_coords_t ;
struct TYPE_14__ {TYPE_2__* gl; TYPE_3__* atlas; } ;
typedef  TYPE_5__ gl_raster_t ;
struct TYPE_12__ {int dirty; } ;
struct TYPE_11__ {int /*<<< orphan*/  mvp_no_rot; int /*<<< orphan*/  shader_data; TYPE_1__* shader; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* set_mvp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_coords ) (int /*<<< orphan*/ ,TYPE_4__ const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_raster_font_upload_atlas (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__ const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_raster_font_draw_vertices(gl_raster_t *font,
      const video_coords_t *coords,
      video_frame_info_t *video_info)
{
   if (font->atlas->dirty)
   {
      gl_raster_font_upload_atlas(font);
      font->atlas->dirty   = false;
   }

   font->gl->shader->set_coords(font->gl->shader_data, coords);
   font->gl->shader->set_mvp(font->gl->shader_data,
         &font->gl->mvp_no_rot);

   glDrawArrays(GL_TRIANGLES, 0, coords->vertices);
}