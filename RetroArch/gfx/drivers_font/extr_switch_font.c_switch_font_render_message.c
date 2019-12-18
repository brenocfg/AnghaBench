#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_2__ switch_font_t ;
struct TYPE_5__ {float (* get_line_height ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AVG_GLPYH_LIMIT ; 
 char* strchr (char const*,char) ; 
 unsigned int strlen (char const*) ; 
 float stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_font_render_line (int /*<<< orphan*/ *,TYPE_2__*,char const*,unsigned int,float,unsigned int const,float,float,unsigned int) ; 

__attribute__((used)) static void switch_font_render_message(
    video_frame_info_t *video_info,
    switch_font_t *font, const char *msg, float scale,
    const unsigned int color, float pos_x, float pos_y,
    unsigned text_align)
{
      int lines = 0;
      float line_height;

      if (!msg || !*msg)
            return;

      /* If the font height is not supported just draw as usual */
      if (!font->font_driver->get_line_height)
      {
            int msgLen = strlen(msg);
            if (msgLen <= AVG_GLPYH_LIMIT)
            {
                  switch_font_render_line(video_info, font, msg, strlen(msg),
                                          scale, color, pos_x, pos_y, text_align);
            }
            return;
      }
      line_height = scale / font->font_driver->get_line_height(font->font_data);

      for (;;)
      {
            const char *delim = strchr(msg, '\n');

            /* Draw the line */
            if (delim)
            {
                  unsigned msg_len = delim - msg;
                  if (msg_len <= AVG_GLPYH_LIMIT)
                  {
                        switch_font_render_line(video_info, font, msg, msg_len,
                                                scale, color, pos_x, pos_y - (float)lines * line_height,
                                                text_align);
                  }
                  msg += msg_len + 1;
                  lines++;
            }
            else
            {
                  unsigned msg_len = strlen(msg);
                  if (msg_len <= AVG_GLPYH_LIMIT)
                  {
                        switch_font_render_line(video_info, font, msg, msg_len,
                                                scale, color, pos_x, pos_y - (float)lines * line_height,
                                                text_align);
                  }
                  break;
            }
      }
}