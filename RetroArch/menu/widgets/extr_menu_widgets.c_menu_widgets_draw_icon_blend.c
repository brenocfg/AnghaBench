#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_coords {int vertices; float* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_7__ {float rotation; float scale_x; float scale_y; int scale_z; int scale_enable; int /*<<< orphan*/ * matrix; } ;
typedef  TYPE_2__ menu_display_ctx_rotate_draw_t ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_8__ {float x; unsigned int y; unsigned int width; unsigned int height; float scale_factor; float rotation; uintptr_t texture; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_3__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 int /*<<< orphan*/  menu_display_draw_blend (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_rotate_z (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_widgets_draw_icon_blend(
      video_frame_info_t *video_info,
      unsigned icon_width,
      unsigned icon_height,
      uintptr_t texture,
      float x, float y,
      unsigned width, unsigned height,
      float rotation, float scale_factor,
      float *color)
{
   menu_display_ctx_rotate_draw_t rotate_draw;
   menu_display_ctx_draw_t draw;
   struct video_coords coords;
   math_matrix_4x4 mymat;

   if (!texture)
      return;

   rotate_draw.matrix       = &mymat;
   rotate_draw.rotation     = rotation;
   rotate_draw.scale_x      = scale_factor;
   rotate_draw.scale_y      = scale_factor;
   rotate_draw.scale_z      = 1;
   rotate_draw.scale_enable = true;

   menu_display_rotate_z(&rotate_draw, video_info);

   coords.vertices      = 4;
   coords.vertex        = NULL;
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;
   coords.color         = color;

   draw.x               = x;
   draw.y               = height - y - icon_height;
   draw.width           = icon_width;
   draw.height          = icon_height;
   draw.scale_factor    = scale_factor;
   draw.rotation        = rotation;
   draw.coords          = &coords;
   draw.matrix_data     = &mymat;
   draw.texture         = texture;
   draw.prim_type       = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id     = 0;

   menu_display_draw_blend(&draw, video_info);
}