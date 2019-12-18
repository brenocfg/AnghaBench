#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_coords {int vertices; float* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_6__ {int x; int y; unsigned int width; unsigned int height; float scale_factor; float rotation; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/  texture; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_2__ menu_display_ctx_draw_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* blend_end ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* blend_begin ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 TYPE_4__* menu_disp ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_white_texture ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void menu_display_draw_quad(
      video_frame_info_t *video_info,
      int x, int y, unsigned w, unsigned h,
      unsigned width, unsigned height,
      float *color)
{
   menu_display_ctx_draw_t draw;
   struct video_coords coords;

   coords.vertices      = 4;
   coords.vertex        = NULL;
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;
   coords.color         = color;

   if (menu_disp && menu_disp->blend_begin)
      menu_disp->blend_begin(video_info);

   draw.x            = x;
   draw.y            = (int)height - y - (int)h;
   draw.width        = w;
   draw.height       = h;
   draw.coords       = &coords;
   draw.matrix_data  = NULL;
   draw.texture      = menu_display_white_texture;
   draw.prim_type    = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id  = 0;
   draw.scale_factor = 1.0f;
   draw.rotation     = 0.0f;

   menu_display_draw(&draw, video_info);

   if (menu_disp && menu_disp->blend_end)
      menu_disp->blend_end(video_info);
}