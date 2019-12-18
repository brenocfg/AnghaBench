#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int width; unsigned int height; int font_msg_color_r; int font_msg_color_g; int font_msg_color_b; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct font_params {int text_align; unsigned int x; double y; int drop_x; int drop_y; float drop_mod; float drop_alpha; int /*<<< orphan*/  color; } ;
struct TYPE_9__ {int ascent; int /*<<< orphan*/  font; TYPE_1__* d3d; } ;
typedef  TYPE_3__ d3dfonts_t ;
struct TYPE_10__ {unsigned int left; unsigned int right; int top; unsigned int bottom; } ;
struct TYPE_7__ {TYPE_4__ font_rect_shifted; TYPE_4__ font_rect; } ;
typedef  TYPE_4__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCOLOR_ARGB (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int DT_CENTER ; 
 unsigned int DT_LEFT ; 
 unsigned int DT_RIGHT ; 
 unsigned int FONT_COLOR_GET_ALPHA (int /*<<< orphan*/ ) ; 
 unsigned int FONT_COLOR_GET_BLUE (int /*<<< orphan*/ ) ; 
 unsigned int FONT_COLOR_GET_GREEN (int /*<<< orphan*/ ) ; 
 unsigned int FONT_COLOR_GET_RED (int /*<<< orphan*/ ) ; 
#define  TEXT_ALIGN_CENTER 130 
#define  TEXT_ALIGN_LEFT 129 
#define  TEXT_ALIGN_RIGHT 128 
 int /*<<< orphan*/  d3d9x_font_draw_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,TYPE_4__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3dfonts_w32_render_msg(video_frame_info_t *video_info,
      void *data, const char *msg, const struct font_params *params)
{
   unsigned format;
   unsigned a, r, g, b;
   RECT rect, rect_shifted;
   RECT *p_rect_shifted             = NULL;
   RECT *p_rect                     = NULL;
   d3dfonts_t *d3dfonts             = (d3dfonts_t*)data;
   unsigned width                   = video_info->width;
   unsigned height                  = video_info->height;
   float drop_mod                   = 0.3f;
   float drop_alpha                 = 1.0f;
   int drop_x                       = -2;
   int drop_y                       = -2;

   if (!d3dfonts || !d3dfonts->d3d || !msg)
      return;

   format         = DT_LEFT;
   p_rect         = &d3dfonts->d3d->font_rect;
   p_rect_shifted = &d3dfonts->d3d->font_rect_shifted;

   if(params)
   {
      a = FONT_COLOR_GET_ALPHA(params->color);
      r = FONT_COLOR_GET_RED(params->color);
      g = FONT_COLOR_GET_GREEN(params->color);
      b = FONT_COLOR_GET_BLUE(params->color);

      switch (params->text_align)
      {
         case TEXT_ALIGN_RIGHT:
            format     = DT_RIGHT;
            rect.left  = 0;
            rect.right = params->x * width;
            break;
         case TEXT_ALIGN_CENTER:
            format     = DT_CENTER;
            rect.left  = (params->x - 1.0) * width;
            rect.right = (params->x + 1.0) * width;
            break;
         case TEXT_ALIGN_LEFT:
         default:
            format     = DT_LEFT;
            rect.left  = params->x * width;
            rect.right = width;
            break;
      }

      rect.top    = (1.0 - params->y) * height - d3dfonts->ascent;
      rect.bottom = height;
      p_rect      = &rect;

      drop_x      = params->drop_x;
      drop_y      = params->drop_y;

      if(drop_x || drop_y)
      {
         drop_mod             = params->drop_mod;
         drop_alpha           = params->drop_alpha;
         rect_shifted         = rect;
         rect_shifted.left   += params->drop_x;
         rect_shifted.right  += params->drop_x;
         rect_shifted.top    -= params->drop_y;
         rect_shifted.bottom -= params->drop_y;
         p_rect_shifted       = &rect_shifted;
      }
   }
   else
   {
      a = 255;
      r = video_info->font_msg_color_r * 255;
      g = video_info->font_msg_color_g * 255;
      b = video_info->font_msg_color_b * 255;
   }

   if(drop_x || drop_y)
   {
      unsigned drop_a = a * drop_alpha;
      unsigned drop_r = r * drop_mod;
      unsigned drop_g = g * drop_mod;
      unsigned drop_b = b * drop_mod;

      d3d9x_font_draw_text(d3dfonts->font, NULL,
            (void*)msg, -1, p_rect_shifted, format,
            D3DCOLOR_ARGB(drop_a , drop_r, drop_g, drop_b));
   }

   d3d9x_font_draw_text(d3dfonts->font, NULL, (void*)msg, -1,
      p_rect, format, D3DCOLOR_ARGB(a, r, g, b));
}