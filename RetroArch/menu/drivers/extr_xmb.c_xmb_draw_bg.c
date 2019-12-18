#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmb_handle_t ;
struct TYPE_18__ {int libretro_running; int menu_shader_pipeline; scalar_t__ xmb_color_theme; float menu_wallpaper_opacity; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct TYPE_17__ {scalar_t__ id; int /*<<< orphan*/  active; } ;
struct TYPE_19__ {uintptr_t texture; unsigned int width; unsigned int height; float* color; int vertex_count; TYPE_1__ pipeline; int /*<<< orphan*/  prim_type; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * vertex; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ menu_display_ctx_draw_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_DISPLAY_PRIM_TRIANGLESTRIP ; 
 scalar_t__ VIDEO_SHADER_MENU ; 
 scalar_t__ VIDEO_SHADER_MENU_2 ; 
 scalar_t__ VIDEO_SHADER_MENU_3 ; 
 scalar_t__ VIDEO_SHADER_MENU_4 ; 
 scalar_t__ VIDEO_SHADER_MENU_5 ; 
 scalar_t__ VIDEO_SHADER_MENU_6 ; 
#define  XMB_SHADER_PIPELINE_BOKEH 132 
#define  XMB_SHADER_PIPELINE_RIBBON 131 
#define  XMB_SHADER_PIPELINE_SIMPLE_SNOW 130 
#define  XMB_SHADER_PIPELINE_SNOW 129 
#define  XMB_SHADER_PIPELINE_SNOWFLAKE 128 
 int XMB_SHADER_PIPELINE_WALLPAPER ; 
 scalar_t__ XMB_THEME_WALLPAPER ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_blend_end (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw_bg (TYPE_3__*,TYPE_2__*,int,float) ; 
 int /*<<< orphan*/  menu_display_draw_gradient (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_draw_pipeline (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  menu_display_set_alpha (float*,float) ; 
 int /*<<< orphan*/  menu_display_set_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xmb_gradient_ident (TYPE_2__*) ; 
 int /*<<< orphan*/  xmb_shader_pipeline_active (TYPE_2__*) ; 

__attribute__((used)) static void xmb_draw_bg(
      xmb_handle_t *xmb,
      video_frame_info_t *video_info,
      unsigned width,
      unsigned height,
      float alpha,
      uintptr_t texture_id,
      float *coord_black,
      float *coord_white)
{
   menu_display_ctx_draw_t draw;

   bool running              = video_info->libretro_running;

   draw.x                    = 0;
   draw.y                    = 0;
   draw.texture              = texture_id;
   draw.width                = width;
   draw.height               = height;
   draw.color                = &coord_black[0];
   draw.vertex               = NULL;
   draw.tex_coord            = NULL;
   draw.vertex_count         = 4;
   draw.prim_type            = MENU_DISPLAY_PRIM_TRIANGLESTRIP;
   draw.pipeline.id          = 0;
   draw.pipeline.active      = xmb_shader_pipeline_active(video_info);

   menu_display_blend_begin(video_info);
   menu_display_set_viewport(video_info->width, video_info->height);

#ifdef HAVE_SHADERPIPELINE
   if (video_info->menu_shader_pipeline > XMB_SHADER_PIPELINE_WALLPAPER
         &&
         (video_info->xmb_color_theme != XMB_THEME_WALLPAPER))
   {
      draw.color = xmb_gradient_ident(video_info);

      if (running)
         menu_display_set_alpha(draw.color, coord_black[3]);
      else
         menu_display_set_alpha(draw.color, coord_white[3]);

      menu_display_draw_gradient(&draw, video_info);

      draw.pipeline.id = VIDEO_SHADER_MENU_2;

      switch (video_info->menu_shader_pipeline)
      {
         case XMB_SHADER_PIPELINE_RIBBON:
            draw.pipeline.id  = VIDEO_SHADER_MENU;
            break;
         case XMB_SHADER_PIPELINE_SIMPLE_SNOW:
            draw.pipeline.id  = VIDEO_SHADER_MENU_3;
            break;
         case XMB_SHADER_PIPELINE_SNOW:
            draw.pipeline.id  = VIDEO_SHADER_MENU_4;
            break;
         case XMB_SHADER_PIPELINE_BOKEH:
            draw.pipeline.id  = VIDEO_SHADER_MENU_5;
            break;
         case XMB_SHADER_PIPELINE_SNOWFLAKE:
            draw.pipeline.id  = VIDEO_SHADER_MENU_6;
            break;
         default:
            break;
      }

      menu_display_draw_pipeline(&draw, video_info);
   }
   else
#endif
   {
      uintptr_t texture           = draw.texture;

      if (video_info->xmb_color_theme != XMB_THEME_WALLPAPER)
         draw.color = xmb_gradient_ident(video_info);

      if (running)
         menu_display_set_alpha(draw.color, coord_black[3]);
      else
         menu_display_set_alpha(draw.color, coord_white[3]);

      if (video_info->xmb_color_theme != XMB_THEME_WALLPAPER)
         menu_display_draw_gradient(&draw, video_info);

      {
         float override_opacity = video_info->menu_wallpaper_opacity;
         bool add_opacity       = false;

         draw.texture           = texture;
         menu_display_set_alpha(draw.color, coord_white[3]);

         if (draw.texture)
            draw.color = &coord_white[0];

         if (running || video_info->xmb_color_theme == XMB_THEME_WALLPAPER)
            add_opacity = true;

         menu_display_draw_bg(&draw, video_info, add_opacity, override_opacity);
      }
   }

   menu_display_draw(&draw, video_info);
   menu_display_blend_end(video_info);
}