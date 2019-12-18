#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {float shadow_offset; } ;
typedef  TYPE_2__ xmb_handle_t ;
struct TYPE_14__ {scalar_t__ xmb_shadows_enable; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct video_coords {int vertices; float* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_15__ {int scale_x; int scale_y; int scale_z; int scale_enable; scalar_t__ rotation; int /*<<< orphan*/ * matrix; } ;
typedef  TYPE_4__ menu_display_ctx_rotate_draw_t ;
struct TYPE_12__ {scalar_t__ id; } ;
struct TYPE_16__ {float width; float height; uintptr_t texture; float x; float y; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_5__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 float* coord_shadow ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_rotate_z (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,float) ; 

__attribute__((used)) static void xmb_draw_thumbnail(
      video_frame_info_t *video_info,
      xmb_handle_t *xmb, float *color,
      unsigned width, unsigned height,
      float x, float y,
      float w, float h, uintptr_t texture)
{
   menu_display_ctx_rotate_draw_t rotate_draw;
   menu_display_ctx_draw_t draw;
   struct video_coords coords;
   math_matrix_4x4 mymat;

   rotate_draw.matrix       = &mymat;
   rotate_draw.rotation     = 0;
   rotate_draw.scale_x      = 1;
   rotate_draw.scale_y      = 1;
   rotate_draw.scale_z      = 1;
   rotate_draw.scale_enable = true;

   menu_display_rotate_z(&rotate_draw, video_info);

   coords.vertices          = 4;
   coords.vertex            = NULL;
   coords.tex_coord         = NULL;
   coords.lut_tex_coord     = NULL;

   draw.width               = w;
   draw.height              = h;
   draw.coords              = &coords;
   draw.matrix_data         = &mymat;
   draw.texture             = texture;
   draw.prim_type           = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id         = 0;

   if (video_info->xmb_shadows_enable)
   {
      menu_display_set_alpha(coord_shadow, color[3] * 0.35f);

      coords.color          = coord_shadow;
      draw.x                = x + xmb->shadow_offset;
      draw.y                = height - y - xmb->shadow_offset;

      menu_display_draw(&draw, video_info);
   }

   coords.color             = (const float*)color;
   draw.x                   = x;
   draw.y                   = height - y;

   menu_display_set_alpha(color, 1.0f);

   menu_display_draw(&draw, video_info);
}