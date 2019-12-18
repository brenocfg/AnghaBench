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
struct TYPE_7__ {int /*<<< orphan*/  alpha; } ;
typedef  TYPE_2__ xmb_handle_t ;
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_coords {int vertices; float* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_8__ {unsigned int width; unsigned int height; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/  texture; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ menu_display_ctx_draw_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  menu_display_blend_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_blend_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_white_texture ; 

__attribute__((used)) static void xmb_draw_dark_layer(
      xmb_handle_t *xmb,
      video_frame_info_t *video_info,
      unsigned width,
      unsigned height)
{
   menu_display_ctx_draw_t draw;
   struct video_coords coords;
   float black[16] = {
      0, 0, 0, 1,
      0, 0, 0, 1,
      0, 0, 0, 1,
      0, 0, 0, 1,
   };

   menu_display_set_alpha(black, MIN(xmb->alpha, 0.75));

   coords.vertices      = 4;
   coords.vertex        = NULL;
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;
   coords.color         = &black[0];

   draw.x           = 0;
   draw.y           = 0;
   draw.width       = width;
   draw.height      = height;
   draw.coords      = &coords;
   draw.matrix_data = NULL;
   draw.texture     = menu_display_white_texture;
   draw.prim_type   = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id = 0;

   menu_display_blend_begin(video_info);
   menu_display_draw(&draw, video_info);
   menu_display_blend_end(video_info);
}