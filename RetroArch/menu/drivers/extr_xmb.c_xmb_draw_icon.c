#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ xmb_shadows_enable; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct video_coords {int vertices; float const* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_7__ {scalar_t__ id; } ;
struct TYPE_9__ {int width; int height; float rotation; float scale_factor; uintptr_t texture; float x; unsigned int y; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_3__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 float const* coord_shadow ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float const*,float) ; 

__attribute__((used)) static void xmb_draw_icon(
      video_frame_info_t *video_info,
      int icon_size,
      math_matrix_4x4 *mymat,
      uintptr_t texture,
      float x,
      float y,
      unsigned width,
      unsigned height,
      float alpha,
      float rotation,
      float scale_factor,
      float *color,
      float shadow_offset)
{
   menu_display_ctx_draw_t draw;
   struct video_coords coords;

   if (
         (x < (-icon_size / 2.0f)) ||
         (x > width)               ||
         (y < (icon_size  / 2.0f)) ||
         (y > height + icon_size)
      )
      return;

   coords.vertices      = 4;
   coords.vertex        = NULL;
   coords.tex_coord     = NULL;
   coords.lut_tex_coord = NULL;

   draw.width           = icon_size;
   draw.height          = icon_size;
   draw.rotation        = rotation;
   draw.scale_factor    = scale_factor;
#if defined(VITA) || defined(WIIU)
   draw.width          *= scale_factor;
   draw.height         *= scale_factor;
#endif
   draw.coords          = &coords;
   draw.matrix_data     = mymat;
   draw.texture         = texture;
   draw.prim_type       = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id     = 0;

   if (video_info->xmb_shadows_enable)
   {
      menu_display_set_alpha(coord_shadow, color[3] * 0.35f);

      coords.color      = coord_shadow;
      draw.x            = x + shadow_offset;
      draw.y            = height - y - shadow_offset;

#if defined(VITA) || defined(WIIU)
      if (scale_factor < 1)
      {
         draw.x         = draw.x + (icon_size-draw.width)/2;
         draw.y         = draw.y + (icon_size-draw.width)/2;
      }
#endif
      menu_display_draw(&draw, video_info);
   }

   coords.color         = (const float*)color;
   draw.x               = x;
   draw.y               = height - y;

#if defined(VITA) || defined(WIIU)
   if (scale_factor < 1)
   {
      draw.x            = draw.x + (icon_size-draw.width)/2;
      draw.y            = draw.y + (icon_size-draw.width)/2;
   }
#endif
   menu_display_draw(&draw, video_info);
}