#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {float menu_wallpaper_opacity; float menu_framebuffer_opacity; scalar_t__ libretro_running; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ video_frame_info_t ;
struct TYPE_15__ {int active; int /*<<< orphan*/ * backend_data; scalar_t__ id; } ;
struct TYPE_19__ {int vertex_count; float* color; scalar_t__ texture; TYPE_1__ pipeline; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * matrix_data; int /*<<< orphan*/ * coords; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_5__ menu_display_ctx_draw_t ;
struct TYPE_17__ {int /*<<< orphan*/  list_background; } ;
struct TYPE_16__ {scalar_t__ bg; } ;
struct TYPE_20__ {TYPE_3__ colors; TYPE_2__ textures; } ;
typedef  TYPE_6__ materialui_handle_t ;
typedef  int /*<<< orphan*/  draw_color ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_draw_bg (TYPE_5__*,TYPE_4__*,int,float) ; 
 scalar_t__ menu_display_white_texture ; 

__attribute__((used)) static void materialui_render_background(materialui_handle_t *mui, video_frame_info_t *video_info)
{
   menu_display_ctx_draw_t draw;
   bool add_opacity       = false;
   float opacity_override = 1.0f;
   float draw_color[16]   = {
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f
   };

   /* Configure draw object */
   draw.x                     = 0;
   draw.y                     = 0;
   draw.width                 = video_info->width;
   draw.height                = video_info->height;
   draw.coords                = NULL;
   draw.matrix_data           = NULL;
   draw.prim_type             = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.vertex                = NULL;
   draw.tex_coord             = NULL;
   draw.vertex_count          = 4;
   draw.pipeline.id           = 0;
   draw.pipeline.active       = false;
   draw.pipeline.backend_data = NULL;
   draw.color                 = draw_color;

   if (mui->textures.bg && !video_info->libretro_running)
   {
      draw.texture = mui->textures.bg;

      /* We are showing a wallpaper - set opacity
       * override to menu_wallpaper_opacity */
      add_opacity      = true;
      opacity_override = video_info->menu_wallpaper_opacity;
   }
   else
   {
      draw.texture = menu_display_white_texture;

      /* Copy 'list_background' colour to draw colour */
      memcpy(draw_color, mui->colors.list_background, sizeof(draw_color));

      /* We are not showing a wallpaper - if content
       * is running, set opacity override to
       * menu_framebuffer_opacity */
      if (video_info->libretro_running)
      {
         add_opacity      = true;
         opacity_override = video_info->menu_framebuffer_opacity;
      }
   }

   /* Draw background */
   menu_display_blend_begin(video_info);
   menu_display_draw_bg(&draw, video_info, add_opacity, opacity_override);
   menu_display_draw(&draw, video_info);
   menu_display_blend_end(video_info);
}