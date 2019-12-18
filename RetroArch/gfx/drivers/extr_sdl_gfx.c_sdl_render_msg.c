#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  unsigned int uint32_t ;
struct font_glyph {int width; int height; int draw_offset_x; int draw_offset_y; int atlas_offset_x; int atlas_offset_y; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct font_atlas {unsigned int* buffer; int width; } ;
struct TYPE_11__ {unsigned int video_msg_pos_x; float video_msg_pos_y; } ;
struct TYPE_13__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_14__ {unsigned int font_r; unsigned int font_g; unsigned int font_b; int /*<<< orphan*/  font; TYPE_2__* font_driver; } ;
typedef  TYPE_4__ sdl_video_t ;
struct TYPE_16__ {unsigned int Rshift; unsigned int Gshift; unsigned int Bshift; } ;
struct TYPE_15__ {int pitch; scalar_t__ pixels; } ;
struct TYPE_12__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,unsigned int) ;struct font_atlas* (* get_atlas ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ SDL_Surface ;
typedef  TYPE_6__ SDL_PixelFormat ;

/* Variables and functions */
 TYPE_3__* config_get_ptr () ; 
 struct font_atlas* stub1 (int /*<<< orphan*/ ) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sdl_render_msg(sdl_video_t *vid, SDL_Surface *buffer,
      const char *msg, unsigned width, unsigned height, const SDL_PixelFormat *fmt)
{
   int x, y, msg_base_x, msg_base_y;
   unsigned rshift, gshift, bshift;
   const struct font_atlas *atlas = NULL;
   settings_t *settings = config_get_ptr();

   if (!vid->font)
      return;

   atlas = vid->font_driver->get_atlas(vid->font);

   msg_base_x = settings->floats.video_msg_pos_x * width;
   msg_base_y = (1.0f - settings->floats.video_msg_pos_y) * height;

   rshift = fmt->Rshift;
   gshift = fmt->Gshift;
   bshift = fmt->Bshift;

   for (; *msg; msg++)
   {
      int glyph_width, glyph_height;
      int base_x, base_y, max_width, max_height;
      uint32_t *out      = NULL;
      const uint8_t *src = NULL;
      const struct font_glyph *glyph = vid->font_driver->get_glyph(vid->font, (uint8_t)*msg);
      if (!glyph)
         continue;

      glyph_width  = glyph->width;
      glyph_height = glyph->height;

      base_x = msg_base_x + glyph->draw_offset_x;
      base_y = msg_base_y + glyph->draw_offset_y;
      src    = atlas->buffer + glyph->atlas_offset_x
         + glyph->atlas_offset_y * atlas->width;

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

      max_width  = width - base_x;
      max_height = height - base_y;

      if (max_width <= 0 || max_height <= 0)
         continue;

      if (glyph_width > max_width)
         glyph_width = max_width;
      if (glyph_height > max_height)
         glyph_height = max_height;

      out = (uint32_t*)buffer->pixels + base_y * (buffer->pitch >> 2) + base_x;

      for (y = 0; y < glyph_height; y++, src += atlas->width, out += buffer->pitch >> 2)
      {
         for (x = 0; x < glyph_width; x++)
         {
            unsigned blend = src[x];
            unsigned out_pix = out[x];
            unsigned r = (out_pix >> rshift) & 0xff;
            unsigned g = (out_pix >> gshift) & 0xff;
            unsigned b = (out_pix >> bshift) & 0xff;

            unsigned out_r = (r * (256 - blend) + vid->font_r * blend) >> 8;
            unsigned out_g = (g * (256 - blend) + vid->font_g * blend) >> 8;
            unsigned out_b = (b * (256 - blend) + vid->font_b * blend) >> 8;
            out[x] = (out_r << rshift) | (out_g << gshift) | (out_b << bshift);
         }
      }

      msg_base_x += glyph->advance_x;
      msg_base_y += glyph->advance_y;
   }
}