#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct g2d_image {int width; float height; } ;
struct font_glyph {int draw_offset_x; int draw_offset_y; int width; int height; int atlas_offset_x; int atlas_offset_y; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct font_atlas {int width; int /*<<< orphan*/ * buffer; } ;
struct exynos_video {int /*<<< orphan*/  font_color; int /*<<< orphan*/  font; TYPE_2__* font_driver; struct exynos_data* data; } ;
struct exynos_data {int /*<<< orphan*/  g2d; struct g2d_image** src; } ;
struct TYPE_5__ {int video_msg_pos_x; float video_msg_pos_y; } ;
struct TYPE_7__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_6__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct font_atlas* (* get_atlas ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t EXYNOS_IMAGE_FONT ; 
 TYPE_3__* config_get_ptr () ; 
 int exynos_blend_font (struct exynos_data*) ; 
 scalar_t__ exynos_clear_buffer (int /*<<< orphan*/ ,struct g2d_image*) ; 
 int /*<<< orphan*/  exynos_put_glyph_rgba4444 (struct exynos_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 struct font_atlas* stub1 (int /*<<< orphan*/ ) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_render_msg(struct exynos_video *vid,
      const char *msg)
{
   const struct font_atlas *atlas;
   struct exynos_data *pdata = vid->data;
   struct g2d_image *dst     = pdata->src[EXYNOS_IMAGE_FONT];
   settings_t *settings      = config_get_ptr();
   int msg_base_x            = settings->floats.video_msg_pos_x * dst->width;
   int msg_base_y            = (1.0f - settings->floats.video_msg_pos_y) * dst->height;

   if (!vid->font || !vid->font_driver)
      return -1;

   if (exynos_clear_buffer(pdata->g2d, dst) != 0)
      return -1;

   atlas = vid->font_driver->get_atlas(vid->font);

   for (; *msg; ++msg)
   {
      int base_x, base_y;
      int glyph_width, glyph_height;
      const uint8_t *src = NULL;
      const struct font_glyph *glyph = vid->font_driver->get_glyph(vid->font, (uint8_t)*msg);
      if (!glyph)
         continue;

      base_x = msg_base_x + glyph->draw_offset_x;
      base_y = msg_base_y + glyph->draw_offset_y;

      const int max_width  = dst->width - base_x;
      const int max_height = dst->height - base_y;

      glyph_width  = glyph->width;
      glyph_height = glyph->height;

      src = atlas->buffer + glyph->atlas_offset_x + glyph->atlas_offset_y * atlas->width;

      if (base_x < 0)
      {
         src -= base_x;
         glyph_width += base_x;
         base_x = 0;
      }

      if (base_y < 0)
      {
         src -= base_y * (int)atlas->width;
         glyph_height += base_y;
         base_y = 0;
      }

      if (max_width <= 0 || max_height <= 0)
         continue;

      if (glyph_width > max_width)
         glyph_width = max_width;
      if (glyph_height > max_height)
         glyph_height = max_height;

      exynos_put_glyph_rgba4444(pdata, src, vid->font_color,
            glyph_width, glyph_height,
            atlas->width, base_x, base_y);

      msg_base_x += glyph->advance_x;
      msg_base_y += glyph->advance_y;
   }

   return exynos_blend_font(pdata);
}