#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ height; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct video_coords {int vertices; float const* color; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; } ;
struct TYPE_16__ {scalar_t__ status; float alpha; int /*<<< orphan*/  texture; scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_3__ menu_thumbnail_t ;
struct TYPE_17__ {float rotation; float scale_x; float scale_y; float scale_z; int scale_enable; int /*<<< orphan*/ * matrix; } ;
typedef  TYPE_4__ menu_display_ctx_rotate_draw_t ;
struct TYPE_14__ {scalar_t__ id; } ;
struct TYPE_18__ {unsigned int width; unsigned int height; float scale_factor; float rotation; float x; float y; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/  texture; int /*<<< orphan*/ * matrix_data; struct video_coords* coords; } ;
typedef  TYPE_5__ menu_display_ctx_draw_t ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_AVAILABLE ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_rotate_z (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,float) ; 

void menu_thumbnail_draw(
      video_frame_info_t *video_info, menu_thumbnail_t *thumbnail,
      float x, float y, unsigned width, unsigned height,
      float alpha, float scale_factor)
{
   /* Sanity check */
   if (!video_info || !thumbnail ||
       (width < 1) || (height < 1) || (alpha <= 0.0f) || (scale_factor <= 0.0f))
      return;

   /* Only draw thumbnail if it is available... */
   if (thumbnail->status == MENU_THUMBNAIL_STATUS_AVAILABLE)
   {
      menu_display_ctx_rotate_draw_t rotate_draw;
      menu_display_ctx_draw_t draw;
      struct video_coords coords;
      math_matrix_4x4 mymat;
      float draw_width;
      float draw_height;
      float display_aspect;
      float thumbnail_aspect;
      float thumbnail_alpha     = thumbnail->alpha * alpha;
      float thumbnail_color[16] = {
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f, 1.0f
      };

      /* Set thumbnail opacity */
      if (thumbnail_alpha <= 0.0f)
         return;
      else if (thumbnail_alpha < 1.0f)
         menu_display_set_alpha(thumbnail_color, thumbnail_alpha);

      /* Get thumbnail dimensions */
      display_aspect   = (float)width            / (float)height;
      thumbnail_aspect = (float)thumbnail->width / (float)thumbnail->height;

      if (thumbnail_aspect > display_aspect)
      {
         draw_width  = (float)width;
         draw_height = (float)thumbnail->height * (draw_width / (float)thumbnail->width);
      }
      else
      {
         draw_height = (float)height;
         draw_width  = (float)thumbnail->width * (draw_height / (float)thumbnail->height);
      }

      /* Account for scale factor
       * > We have to do it like this rather than using the
       *   draw.scale_factor parameter, because the latter
       *   clips off any part of the expanded image that
       *   extends beyond the bounding box... */
      draw_width  *= scale_factor;
      draw_height *= scale_factor;

      menu_display_blend_begin(video_info);

      /* Perform 'rotation' step
       * > Note that rotation does not actually work...
       * > It rotates the image all right, but distorts it
       *   to fit the aspect of the bounding box while clipping
       *   off any 'corners' that extend beyond the bounding box
       * > Since the result is visual garbage, we disable
       *   rotation entirely
       * > But we still have to call menu_display_rotate_z(),
       *   or nothing will be drawn...
       * Note that we also disable scaling here (scale_enable),
       * since we handle scaling internally... */
      rotate_draw.matrix       = &mymat;
      rotate_draw.rotation     = 0.0f;
      rotate_draw.scale_x      = 1.0f;
      rotate_draw.scale_y      = 1.0f;
      rotate_draw.scale_z      = 1.0f;
      rotate_draw.scale_enable = false;

      menu_display_rotate_z(&rotate_draw, video_info);

      /* Configure draw object */
      coords.vertices      = 4;
      coords.vertex        = NULL;
      coords.tex_coord     = NULL;
      coords.lut_tex_coord = NULL;
      coords.color         = (const float*)thumbnail_color;

      draw.width           = (unsigned)draw_width;
      draw.height          = (unsigned)draw_height;
      draw.scale_factor    = 1.0f;
      draw.rotation        = 0.0f;
      draw.coords          = &coords;
      draw.matrix_data     = &mymat;
      draw.texture         = thumbnail->texture;
      draw.prim_type       = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
      draw.pipeline.id     = 0;

      /* > Ensure thumbnail is centred */
      draw.x               = x + ((float)width - draw_width) / 2.0f;
      draw.y               = (float)video_info->height - y - draw_height - ((float)height - draw_height) / 2.0f;

      /* Draw thumbnail */
      menu_display_draw(&draw, video_info);
      menu_display_blend_end(video_info);
   }
}