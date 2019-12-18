#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* buffer; unsigned int width; int dirty; } ;
struct TYPE_5__ {unsigned int scale_factor; TYPE_1__ atlas; } ;
typedef  TYPE_2__ bm_renderer_t ;

/* Variables and functions */
 unsigned int FONT_HEIGHT ; 
 unsigned int FONT_OFFSET (int) ; 
 unsigned int FONT_WIDTH ; 
 int* bitmap_bin ; 

__attribute__((used)) static void char_to_texture(bm_renderer_t *handle, uint8_t letter,
      unsigned atlas_x, unsigned atlas_y)
{
   unsigned y, x;
   uint8_t *target = handle->atlas.buffer + atlas_x +
      atlas_y * handle->atlas.width;

   for (y = 0; y < FONT_HEIGHT; y++)
   {
      for (x = 0; x < FONT_WIDTH; x++)
      {
         unsigned xo, yo;
         unsigned font_pixel = x + y * FONT_WIDTH;
         uint8_t rem         = 1 << (font_pixel & 7);
         unsigned offset     = font_pixel >> 3;
         uint8_t col         = (bitmap_bin[FONT_OFFSET(letter) + offset] & rem) ? 0xff : 0;
         uint8_t *dst        = target;

         dst                += x * handle->scale_factor;
         dst                += y * handle->scale_factor * handle->atlas.width;

         for (yo = 0; yo < handle->scale_factor; yo++)
            for (xo = 0; xo < handle->scale_factor; xo++)
               dst[xo + yo * handle->atlas.width] = col;
      }
   }
   handle->atlas.dirty = true;
}