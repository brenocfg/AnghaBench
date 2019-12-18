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
struct TYPE_10__ {TYPE_3__* vita; int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_4__ vita_font_t ;
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_8__ {float height; } ;
struct TYPE_9__ {TYPE_2__ vp; } ;
struct TYPE_7__ {float (* get_line_height ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 float stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vita2d_font_render_line (int /*<<< orphan*/ *,TYPE_4__*,char const*,unsigned int,float,unsigned int const,float,float,unsigned int) ; 

__attribute__((used)) static void vita2d_font_render_message(
      video_frame_info_t *video_info,
      vita_font_t *font, const char *msg, float scale,
      const unsigned int color, float pos_x, float pos_y,
      unsigned text_align)
{
   float line_height;
   int lines = 0;

   if (!msg || !*msg)
      return;

   /* If the font height is not supported just draw as usual */
   if (!font->font_driver->get_line_height)
   {
      vita2d_font_render_line(video_info, font, msg, strlen(msg),
            scale, color, pos_x, pos_y, text_align);
      return;
   }

   line_height = font->font_driver->get_line_height(font->font_data) *
                     scale / font->vita->vp.height;

   for (;;)
   {
      const char *delim = strchr(msg, '\n');
      unsigned msg_len  = (delim) ? (delim - msg) : strlen(msg);

      vita2d_font_render_line(video_info, font, msg, msg_len,
            scale, color, pos_x, pos_y - (float)lines * line_height,
            text_align);

      /* Draw the line */
      if (!delim)
         break;

      msg += msg_len + 1;
      lines++;
   }
}