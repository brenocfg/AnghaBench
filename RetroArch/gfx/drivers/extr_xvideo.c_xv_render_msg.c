#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int* luma_index; unsigned int chroma_u_index; unsigned int chroma_v_index; unsigned int font_y; unsigned int font_u; unsigned int font_v; TYPE_3__* image; int /*<<< orphan*/  font; TYPE_2__* font_driver; } ;
typedef  TYPE_4__ xv_t ;
typedef  int uint8_t ;
struct font_glyph {int draw_offset_x; int draw_offset_y; int width; int height; int atlas_offset_x; int atlas_offset_y; scalar_t__ advance_y; scalar_t__ advance_x; } ;
struct font_atlas {int* buffer; int width; } ;
struct TYPE_8__ {unsigned int video_msg_pos_x; float video_msg_pos_y; } ;
struct TYPE_12__ {TYPE_1__ floats; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {struct font_glyph* (* get_glyph ) (int /*<<< orphan*/ ,int) ;struct font_atlas* (* get_atlas ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_5__* config_get_ptr () ; 
 struct font_atlas* stub1 (int /*<<< orphan*/ ) ; 
 struct font_glyph* stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xv_render_msg(xv_t *xv, const char *msg,
      unsigned width, unsigned height)
{
   int x, y, msg_base_x, msg_base_y;
   unsigned i, luma_index[2], pitch;
   unsigned chroma_u_index, chroma_v_index;
   settings_t *settings = config_get_ptr();
   const struct font_atlas *atlas = NULL;

   if (!xv->font)
      return;

   atlas          = xv->font_driver->get_atlas(xv->font);

   msg_base_x     = settings->floats.video_msg_pos_x * width;
   msg_base_y     = height * (1.0f - settings->floats.video_msg_pos_y);

   luma_index[0]  = xv->luma_index[0];
   luma_index[1]  = xv->luma_index[1];

   chroma_u_index = xv->chroma_u_index;
   chroma_v_index = xv->chroma_v_index;

   pitch          = width << 1; /* YUV formats used are 16 bpp. */

   for (; *msg; msg++)
   {
      int base_x, base_y, glyph_width, glyph_height, max_width, max_height;
      const uint8_t *src             = NULL;
      uint8_t *out                   = NULL;
      const struct font_glyph *glyph =
         xv->font_driver->get_glyph(xv->font, (uint8_t)*msg);

      if (!glyph)
         continue;

      /* Make sure we always start on the correct boundary
       * so the indices are correct. */
      base_x          = (msg_base_x + glyph->draw_offset_x + 1) & ~1;
      base_y          = msg_base_y + glyph->draw_offset_y;

      glyph_width     = glyph->width;
      glyph_height    = glyph->height;

      src             = atlas->buffer + glyph->atlas_offset_x +
                        glyph->atlas_offset_y * atlas->width;

      if (base_x < 0)
      {
         src          -= base_x;
         glyph_width  += base_x;
         base_x = 0;
      }

      if (base_y < 0)
      {
         src          -= base_y * (int)atlas->width;
         glyph_height += base_y;
         base_y = 0;
      }

      max_width        = width - base_x;
      max_height       = height - base_y;

      if (max_width <= 0 || max_height <= 0)
         continue;

      if (glyph_width > max_width)
         glyph_width   = max_width;
      if (glyph_height > max_height)
         glyph_height  = max_height;

      out = (uint8_t*)xv->image->data + base_y * pitch + (base_x << 1);

      for (y = 0; y < glyph_height; y++, src += atlas->width, out += pitch)
      {
         /* 2 input pixels => 4 bytes (2Y, 1U, 1V). */

         for (x = 0; x < glyph_width; x += 2)
         {
            unsigned alpha[2], alpha_sub, blended;
            int out_x = x << 1;

            alpha[0] = src[x + 0];
            alpha[1] = 0;

            if (x + 1 < glyph_width)
               alpha[1] = src[x + 1];

            /* Blended alpha for the sub-sampled U/V channels. */
            alpha_sub = (alpha[0] + alpha[1]) >> 1;

            for (i = 0; i < 2; i++)
            {
               unsigned blended = (xv->font_y * alpha[i]
                     + ((256 - alpha[i]) * out[out_x + luma_index[i]])) >> 8;
               out[out_x + luma_index[i]] = blended;
            }

            /* Blend chroma channels */
            blended = (xv->font_u * alpha_sub
                  + ((256 - alpha_sub) * out[out_x + chroma_u_index])) >> 8;
            out[out_x + chroma_u_index] = blended;

            blended = (xv->font_v * alpha_sub
                  + ((256 - alpha_sub) * out[out_x + chroma_v_index])) >> 8;
            out[out_x + chroma_v_index] = blended;
         }
      }

      msg_base_x += glyph->advance_x;
      msg_base_y += glyph->advance_y;
   }
}