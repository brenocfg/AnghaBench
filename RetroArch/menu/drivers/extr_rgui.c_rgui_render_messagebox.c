#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct string_list {size_t size; TYPE_1__* elems; } ;
struct TYPE_8__ {int /*<<< orphan*/  shadow_color; int /*<<< orphan*/  normal_color; int /*<<< orphan*/  bg_light_color; int /*<<< orphan*/  bg_dark_color; int /*<<< orphan*/  border_light_color; int /*<<< orphan*/  border_dark_color; } ;
struct TYPE_9__ {int border_thickness; int bg_thickness; TYPE_2__ colors; scalar_t__ shadow_enable; } ;
typedef  TYPE_3__ rgui_t ;
struct TYPE_11__ {scalar_t__ data; } ;
struct TYPE_10__ {unsigned int width; } ;
struct TYPE_7__ {char* data; } ;

/* Variables and functions */
 int FONT_HEIGHT_STRIDE ; 
 unsigned int FONT_WIDTH_STRIDE ; 
 unsigned int MAX (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  blit_line (unsigned int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_get_fb_size (unsigned int*,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  rgui_color_rect (scalar_t__,unsigned int,unsigned int,int,int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgui_fill_rect (scalar_t__,unsigned int,unsigned int,int,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_6__ rgui_frame_buf ; 
 TYPE_4__ rgui_term_layout ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 unsigned int utf8len (char const*) ; 

__attribute__((used)) static void rgui_render_messagebox(rgui_t *rgui, const char *message)
{
   int x, y;
   size_t i, fb_pitch;
   unsigned fb_width, fb_height;
   unsigned width, glyphs_width, height;
   struct string_list *list   = NULL;

   if (!message || !*message)
      return;

   list = string_split(message, "\n");
   if (!list)
      return;
   if (list->elems == 0)
      goto end;

   width        = 0;
   glyphs_width = 0;

   menu_display_get_fb_size(&fb_width, &fb_height,
         &fb_pitch);

   for (i = 0; i < list->size; i++)
   {
      unsigned line_width;
      char     *msg   = list->elems[i].data;
      unsigned msglen = (unsigned)utf8len(msg);

      if (msglen > rgui_term_layout.width)
      {
         msg[rgui_term_layout.width - 2] = '.';
         msg[rgui_term_layout.width - 1] = '.';
         msg[rgui_term_layout.width - 0] = '.';
         msg[rgui_term_layout.width + 1] = '\0';
         msglen = rgui_term_layout.width;
      }

      line_width   = msglen * FONT_WIDTH_STRIDE - 1 + 6 + 10;
      width        = MAX(width, line_width);
      glyphs_width = MAX(glyphs_width, msglen);
   }

   height = (unsigned)(FONT_HEIGHT_STRIDE * list->size + 6 + 10);
   x      = (fb_width  - width) / 2;
   y      = (fb_height - height) / 2;

   if (rgui_frame_buf.data)
   {
      uint16_t border_dark_color  = rgui->colors.border_dark_color;
      uint16_t border_light_color = rgui->colors.border_light_color;
      bool border_thickness       = rgui->border_thickness;

      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            x + 5, y + 5, width - 10, height - 10,
            rgui->colors.bg_dark_color, rgui->colors.bg_light_color, rgui->bg_thickness);

      /* Note: We draw borders around message boxes regardless
       * of the rgui->border_enable setting, because they look
       * ridiculous without... */

      /* Draw drop shadow, if required */
      if (rgui->shadow_enable)
      {
         uint16_t shadow_color = rgui->colors.shadow_color;

         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               x + 5, y + 5, 1, height - 5, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               x + 5, y + 5, width - 5, 1, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               x + width, y + 1, 1, height, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               x + 1, y + height, width, 1, shadow_color);
      }

      /* Draw border */
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            x, y, width - 5, 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            x + width - 5, y, 5, height - 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            x + 5, y + height - 5, width - 5, 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            x, y + 5, 5, height - 5,
            border_dark_color, border_light_color, border_thickness);
   }

   for (i = 0; i < list->size; i++)
   {
      const char *msg = list->elems[i].data;
      int offset_x    = (int)(FONT_WIDTH_STRIDE * (glyphs_width - utf8len(msg)) / 2);
      int offset_y    = (int)(FONT_HEIGHT_STRIDE * i);

      if (rgui_frame_buf.data)
         blit_line(fb_width, x + 8 + offset_x, y + 8 + offset_y, msg,
               rgui->colors.normal_color, rgui->colors.shadow_color);
   }

end:
   string_list_free(list);
}