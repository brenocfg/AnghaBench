#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ userdata; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct TYPE_17__ {TYPE_6__* coords; int /*<<< orphan*/  prim_type; scalar_t__ matrix_data; scalar_t__ texture; } ;
typedef  TYPE_4__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_15__ {int /*<<< orphan*/  color; } ;
struct TYPE_18__ {int /*<<< orphan*/  white_color_ptr; TYPE_2__ coords; int /*<<< orphan*/  shader_data; TYPE_1__* shader; } ;
typedef  TYPE_5__ gl_t ;
struct TYPE_19__ {int /*<<< orphan*/  vertices; void* lut_tex_coord; void* tex_coord; scalar_t__ vertex; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* set_mvp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_coords ) (int /*<<< orphan*/ ,TYPE_6__*) ;} ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ menu_display_gl_discard_draw_rectangle (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ menu_display_gl_get_default_mvp (TYPE_3__*) ; 
 void* menu_display_gl_get_default_tex_coords () ; 
 scalar_t__ menu_display_gl_get_default_vertices () ; 
 int /*<<< orphan*/  menu_display_gl_viewport (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_prim_to_gl_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_display_gl_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   gl_t             *gl          = (gl_t*)video_info->userdata;

   if (!gl || !draw)
      return;

#ifdef MALI_BUG
   if (menu_display_gl_discard_draw_rectangle(draw, video_info))
   {
      /*RARCH_WARN("[Menu]: discarded draw rect: %.4i %.4i %.4i %.4i\n",
        (int)draw->x, (int)draw->y, (int)draw->width, (int)draw->height);*/
      return;
   }
#endif

   if (!draw->coords->vertex)
      draw->coords->vertex = menu_display_gl_get_default_vertices();
   if (!draw->coords->tex_coord)
      draw->coords->tex_coord = menu_display_gl_get_default_tex_coords();
   if (!draw->coords->lut_tex_coord)
      draw->coords->lut_tex_coord = menu_display_gl_get_default_tex_coords();

   menu_display_gl_viewport(draw, video_info);
   glBindTexture(GL_TEXTURE_2D, (GLuint)draw->texture);

   gl->shader->set_coords(gl->shader_data, draw->coords);
   gl->shader->set_mvp(gl->shader_data,
         draw->matrix_data ? (math_matrix_4x4*)draw->matrix_data
      : (math_matrix_4x4*)menu_display_gl_get_default_mvp(video_info));


   glDrawArrays(menu_display_prim_to_gl_enum(
            draw->prim_type), 0, draw->coords->vertices);

   gl->coords.color     = gl->white_color_ptr;
}