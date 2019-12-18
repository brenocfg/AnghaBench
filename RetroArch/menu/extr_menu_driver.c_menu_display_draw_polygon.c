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
struct video_coords {int vertices; float* vertex; float* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_6__ {unsigned int width; unsigned int height; float scale_factor; float rotation; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/  texture; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ menu_display_ctx_draw_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* blend_end ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* blend_begin ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 TYPE_4__* menu_disp ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_white_texture ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void menu_display_draw_polygon(
      video_frame_info_t *video_info,
      int x1, int y1,
      int x2, int y2,
      int x3, int y3,
      int x4, int y4,
      unsigned width, unsigned height,
      float *color)
{
   menu_display_ctx_draw_t draw;
   struct video_coords coords;

   float vertex[8];

   vertex[0]             = x1 / (float)width;
   vertex[1]             = y1 / (float)height;
   vertex[2]             = x2 / (float)width;
   vertex[3]             = y2 / (float)height;
   vertex[4]             = x3 / (float)width;
   vertex[5]             = y3 / (float)height;
   vertex[6]             = x4 / (float)width;
   vertex[7]             = y4 / (float)height;

   coords.vertices      = 4;
   coords.vertex        = &vertex[0];
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;
   coords.color         = color;

   if (menu_disp && menu_disp->blend_begin)
      menu_disp->blend_begin(video_info);

   draw.x            = 0;
   draw.y            = 0;
   draw.width        = width;
   draw.height       = height;
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