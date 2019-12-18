#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ userdata; } ;
typedef  TYPE_4__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {unsigned int full_width; unsigned int full_height; } ;
struct TYPE_14__ {unsigned int* out_buffer; int stride; TYPE_1__ vp; } ;
typedef  TYPE_5__ switch_video_t ;
struct TYPE_15__ {TYPE_3__* atlas; int /*<<< orphan*/  font_data; TYPE_2__* font_driver; } ;
typedef  TYPE_6__ switch_font_t ;
struct font_glyph {int draw_offset_x; int draw_offset_y; int width; int height; int atlas_offset_x; int atlas_offset_y; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct TYPE_12__ {int width; int /*<<< orphan*/ * buffer; } ;
struct TYPE_11__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;

/* Variables and functions */
#define  TEXT_ALIGN_CENTER 129 
#define  TEXT_ALIGN_RIGHT 128 
 int roundf (float) ; 
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 int switch_font_get_message_width (TYPE_6__*,char const*,unsigned int,float) ; 
 unsigned int utf8_walk (char const**) ; 

__attribute__((used)) static void switch_font_render_line(
    video_frame_info_t *video_info,
    switch_font_t *font, const char *msg, unsigned msg_len,
    float scale, const unsigned int color, float pos_x,
    float pos_y, unsigned text_align)
{
      switch_video_t* sw = (switch_video_t*)video_info->userdata;

      if(!sw)
         return;

      int delta_x = 0;
      int delta_y = 0;

      unsigned fbWidth = sw->vp.full_width;
      unsigned fbHeight = sw->vp.full_height;

      if (sw->out_buffer) {

            int x = roundf(pos_x * fbWidth);
            int y = roundf((1.0f - pos_y) * fbHeight);

            switch (text_align)
            {
            case TEXT_ALIGN_RIGHT:
                  x -= switch_font_get_message_width(font, msg, msg_len, scale);
                  break;
            case TEXT_ALIGN_CENTER:
                  x -= switch_font_get_message_width(font, msg, msg_len, scale) / 2;
                  break;
            }

            for (int i = 0; i < msg_len; i++)
            {
                  int off_x, off_y, tex_x, tex_y, width, height;
                  const char *msg_tmp = &msg[i];
                  unsigned code = utf8_walk(&msg_tmp);
                  unsigned skip = msg_tmp - &msg[i];

                  if (skip > 1)
                        i += skip - 1;

                  const struct font_glyph *glyph =
                        font->font_driver->get_glyph(font->font_data, code);

                  if (!glyph) /* Do something smarter here ... */
                        glyph = font->font_driver->get_glyph(font->font_data, '?');

                  if (!glyph)
                        continue;

                  off_x = x + glyph->draw_offset_x + delta_x;
                  off_y = y + glyph->draw_offset_y + delta_y;
                  width = glyph->width;
                  height = glyph->height;

                  tex_x = glyph->atlas_offset_x;
                  tex_y = glyph->atlas_offset_y;

                  for (int y = tex_y; y < tex_y + height; y++)
                  {
                        uint8_t *row = &font->atlas->buffer[y * font->atlas->width];
                        for (int x = tex_x; x < tex_x + width; x++)
                        {
                              if (!row[x])
                                 continue;
                              int x1 = off_x + (x - tex_x);
                              int y1 = off_y + (y - tex_y);
                              if (x1 < fbWidth && y1 < fbHeight)
                                    sw->out_buffer[y1 * sw->stride / sizeof(uint32_t) + x1] = color;
                        }
                  }

                  delta_x += glyph->advance_x;
                  delta_y += glyph->advance_y;
            }
      }
}