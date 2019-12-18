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
struct font_glyph {scalar_t__ advance_x; } ;
struct TYPE_4__ {int /*<<< orphan*/  font_data; TYPE_1__* font_driver; } ;
typedef  TYPE_2__ gl_raster_t ;
struct TYPE_3__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,char) ;} ;

/* Variables and functions */
 struct font_glyph* stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,char) ; 
 unsigned int utf8_walk (char const**) ; 

__attribute__((used)) static int gl_get_message_width(void *data, const char *msg,
      unsigned msg_len, float scale)
{
   gl_raster_t *font   = (gl_raster_t*)data;
   const char* msg_end = msg + msg_len;
   int delta_x         = 0;

   if (     !font
         || !font->font_driver
         || !font->font_driver->get_glyph
         || !font->font_data )
      return 0;

   while (msg < msg_end)
   {
      unsigned code                  = utf8_walk(&msg);
      const struct font_glyph *glyph = font->font_driver->get_glyph(
            font->font_data, code);

      if (!glyph) /* Do something smarter here ... */
         glyph = font->font_driver->get_glyph(font->font_data, '?');
      if (!glyph)
         continue;

      delta_x += glyph->advance_x;
   }

   return delta_x * scale;
}