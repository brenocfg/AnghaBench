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
typedef  int /*<<< orphan*/  uint8_t ;
struct font_glyph {int draw_offset_x; int draw_offset_y; int width; int height; int atlas_offset_x; int atlas_offset_y; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct font_atlas {int width; int /*<<< orphan*/ * buffer; } ;
struct TYPE_7__ {int video_msg_pos_x; double video_msg_pos_y; } ;
struct TYPE_9__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {int width; double height; int bytes_per_pixel; int /*<<< orphan*/  font_rgb; int /*<<< orphan*/  omap; int /*<<< orphan*/  font; TYPE_2__* font_driver; } ;
typedef  TYPE_4__ omap_video_t ;
struct TYPE_8__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct font_atlas* (* get_atlas ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  omapfb_blend_glyph_argb8888 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  omapfb_blend_glyph_rgb565 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 struct font_atlas* stub1 (int /*<<< orphan*/ ) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_render_msg(omap_video_t *vid, const char *msg)
{
   const struct font_atlas *atlas = NULL;
   settings_t *settings = config_get_ptr();
   int msg_base_x = settings->floats.video_msg_pos_x * vid->width;
   int msg_base_y = (1.0 - settings->floats.video_msg_pos_y) * vid->height;

   if (!vid->font)
      return;

   atlas = vid->font_driver->get_atlas(vid->font);

   for (; *msg; msg++)
   {
      int base_x, base_y;
      int glyph_width, glyph_height;
      const uint8_t *src = NULL;
      const struct font_glyph *glyph =
         vid->font_driver->get_glyph(vid->font, (uint8_t)*msg);

      if (!glyph)
         continue;

      base_x               = msg_base_x + glyph->draw_offset_x;
      base_y               = msg_base_y + glyph->draw_offset_y;

      const int max_width  = vid->width - base_x;
      const int max_height = vid->height - base_y;

      glyph_width          = glyph->width;
      glyph_height         = glyph->height;

      src                  = atlas->buffer + glyph->atlas_offset_x +
         glyph->atlas_offset_y * atlas->width;

      if (base_x < 0)
      {
         src         -= base_x;
         glyph_width += base_x;
         base_x       = 0;
      }

      if (base_y < 0)
      {
         src          -= base_y * (int)atlas->width;
         glyph_height += base_y;
         base_y        = 0;
      }

      if (max_width <= 0 || max_height <= 0)
         continue;

      if (glyph_width > max_width)
         glyph_width = max_width;
      if (glyph_height > max_height)
         glyph_height = max_height;

      if (vid->bytes_per_pixel == 2)
      {
         omapfb_blend_glyph_rgb565(vid->omap, src, vid->font_rgb,
               glyph_width, glyph_height,
               atlas->width, base_x, base_y);
      }
      else
      {
         omapfb_blend_glyph_argb8888(vid->omap, src, vid->font_rgb,
               glyph_width, glyph_height,
               atlas->width, base_x, base_y);
      }

      msg_base_x += glyph->advance_x;
      msg_base_y += glyph->advance_y;
   }
}