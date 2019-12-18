#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_2__ vita_font_t ;
struct font_glyph {scalar_t__ advance_x; } ;
struct TYPE_3__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;

/* Variables and functions */
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 unsigned int utf8_walk (char const**) ; 

__attribute__((used)) static int vita2d_font_get_message_width(void *data, const char *msg,
      unsigned msg_len, float scale)
{
   unsigned i;
   int delta_x       = 0;
   vita_font_t *font = (vita_font_t*)data;

   if (!font)
      return 0;

   for (i = 0; i < msg_len; i++)
   {
      const struct font_glyph *glyph = NULL;
      const char *msg_tmp            = &msg[i];
      unsigned code                  = utf8_walk(&msg_tmp);
      unsigned skip                  = msg_tmp - &msg[i];

      if (skip > 1)
         i += skip - 1;

      glyph = font->font_driver->get_glyph(font->font_data, code);

      if (!glyph) /* Do something smarter here ... */
         glyph = font->font_driver->get_glyph(font->font_data, '?');

      if (!glyph)
         continue;

      delta_x += glyph->advance_x;
   }

   return delta_x * scale;
}