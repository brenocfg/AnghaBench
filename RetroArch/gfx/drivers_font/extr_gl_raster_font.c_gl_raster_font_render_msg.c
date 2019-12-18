#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int width; unsigned int height; float font_msg_pos_x; float font_msg_pos_y; float font_msg_color_r; float font_msg_color_g; float font_msg_color_b; } ;
typedef  TYPE_4__ video_frame_info_t ;
struct font_params {float x; float y; float scale; int full_screen; int text_align; int drop_x; int drop_y; float drop_mod; float drop_alpha; int /*<<< orphan*/  color; } ;
struct TYPE_14__ {TYPE_3__* gl; TYPE_2__* block; scalar_t__ font_driver; scalar_t__ font_data; } ;
typedef  TYPE_5__ gl_raster_t ;
typedef  enum text_alignment { ____Placeholder_text_alignment } text_alignment ;
struct TYPE_10__ {float width; float height; } ;
struct TYPE_12__ {size_t tex_index; int /*<<< orphan*/ * texture; TYPE_1__ vp; } ;
struct TYPE_11__ {int fullscreen; } ;
typedef  float GLfloat ;

/* Variables and functions */
 float FONT_COLOR_GET_ALPHA (int /*<<< orphan*/ ) ; 
 float FONT_COLOR_GET_BLUE (int /*<<< orphan*/ ) ; 
 float FONT_COLOR_GET_GREEN (int /*<<< orphan*/ ) ; 
 float FONT_COLOR_GET_RED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int TEXT_ALIGN_LEFT ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_raster_font_render_message (TYPE_5__*,char const*,float,float*,float,float,int,TYPE_4__*) ; 
 int /*<<< orphan*/  gl_raster_font_setup_viewport (unsigned int,unsigned int,TYPE_5__*,int) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  video_driver_set_viewport (unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static void gl_raster_font_render_msg(
      video_frame_info_t *video_info,
      void *data, const char *msg,
      const struct font_params *params)
{
   GLfloat color[4];
   int drop_x, drop_y;
   GLfloat x, y, scale, drop_mod, drop_alpha;
   enum text_alignment text_align   = TEXT_ALIGN_LEFT;
   bool full_screen                 = false ;
   gl_raster_t                *font = (gl_raster_t*)data;
   unsigned width                   = video_info->width;
   unsigned height                  = video_info->height;

   if (!font || string_is_empty(msg))
      return;

   if (params)
   {
      x           = params->x;
      y           = params->y;
      scale       = params->scale;
      full_screen = params->full_screen;
      text_align  = params->text_align;
      drop_x      = params->drop_x;
      drop_y      = params->drop_y;
      drop_mod    = params->drop_mod;
      drop_alpha  = params->drop_alpha;

      color[0]    = FONT_COLOR_GET_RED(params->color)   / 255.0f;
      color[1]    = FONT_COLOR_GET_GREEN(params->color) / 255.0f;
      color[2]    = FONT_COLOR_GET_BLUE(params->color)  / 255.0f;
      color[3]    = FONT_COLOR_GET_ALPHA(params->color) / 255.0f;

      /* If alpha is 0.0f, turn it into default 1.0f */
      if (color[3] <= 0.0f)
         color[3] = 1.0f;
   }
   else
   {
      x                    = video_info->font_msg_pos_x;
      y                    = video_info->font_msg_pos_y;
      scale                = 1.0f;
      full_screen          = true;
      text_align           = TEXT_ALIGN_LEFT;

      color[0]             = video_info->font_msg_color_r;
      color[1]             = video_info->font_msg_color_g;
      color[2]             = video_info->font_msg_color_b;
      color[3]             = 1.0f;

      drop_x               = -2;
      drop_y               = -2;
      drop_mod             = 0.3f;
      drop_alpha           = 1.0f;
   }

   if (font->block)
      font->block->fullscreen = full_screen;
   else
      gl_raster_font_setup_viewport(width, height, font, full_screen);

   if (!string_is_empty(msg) && font->gl
         && font->font_data  && font->font_driver)
   {
      if (drop_x || drop_y)
      {
         GLfloat color_dark[4];

         color_dark[0] = color[0] * drop_mod;
         color_dark[1] = color[1] * drop_mod;
         color_dark[2] = color[2] * drop_mod;
         color_dark[3] = color[3] * drop_alpha;

         if (font->gl)
            gl_raster_font_render_message(font, msg, scale, color_dark,
                  x + scale * drop_x / font->gl->vp.width, y +
                  scale * drop_y / font->gl->vp.height, text_align,
                  video_info);
      }

      if (font->gl)
         gl_raster_font_render_message(font, msg, scale, color,
               x, y, text_align, video_info);
   }

   if (!font->block && font->gl)
   {
      /* restore viewport */
      glBindTexture(GL_TEXTURE_2D, font->gl->texture[font->gl->tex_index]);

      glDisable(GL_BLEND);
      video_driver_set_viewport(width, height, false, true);
   }
}