#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int MAX_FB_WIDTH ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

__attribute__((used)) static void rgui_fill_rect(
      uint16_t *data,
      unsigned fb_width, unsigned fb_height,
      unsigned x, unsigned y,
      unsigned width, unsigned height,
      uint16_t dark_color, uint16_t light_color,
      bool thickness)
{
   unsigned x_index, y_index;
   unsigned x_start = x <= fb_width  ? x : fb_width;
   unsigned y_start = y <= fb_height ? y : fb_height;
   unsigned x_end   = x + width;
   unsigned y_end   = y + height;
   size_t x_size;
   uint16_t scanline_even[MAX_FB_WIDTH]; /* Initial values don't matter here */
   uint16_t scanline_odd[MAX_FB_WIDTH];

   /* Note: unlike rgui_color_rect() and rgui_draw_particle(),
    * this function is frequently used to fill large areas.
    * We therefore gain significant performance benefits
    * from using memcpy() tricks... */

   x_end  = x_end <= fb_width  ? x_end : fb_width;
   y_end  = y_end <= fb_height ? y_end : fb_height;
   x_size = (x_end - x_start) * sizeof(uint16_t);

   /* Sanity check */
   if (x_size == 0)
      return;

   /* If dark_color and light_color are the same,
    * perform a solid fill */
   if (dark_color == light_color)
   {
      uint16_t *src = scanline_even + x_start;
      uint16_t *dst = data + x_start;

      /* Populate source array */
      for (x_index = x_start; x_index < x_end; x_index++)
         *(scanline_even + x_index) = dark_color;

      /* Fill destination array */
      for (y_index = y_start; y_index < y_end; y_index++)
         memcpy(dst + (y_index * fb_width), src, x_size);
   }
   else if (thickness)
   {
      uint16_t *src_a      = NULL;
      uint16_t *src_b      = NULL;
      uint16_t *src_c      = NULL;
      uint16_t *src_d      = NULL;
      uint16_t *dst        = data + x_start;

      /* Determine in which order the source arrays
       * should be copied */
      switch (y_start & 0x3)
      {
         case 0x1:
            src_a = scanline_even + x_start;
            src_b = scanline_odd  + x_start;
            src_c = src_b;
            src_d = src_a;
            break;
         case 0x2:
            src_a = scanline_odd  + x_start;
            src_b = src_a;
            src_c = scanline_even + x_start;
            src_d = src_c;
            break;
         case 0x3:
            src_a = scanline_odd  + x_start;
            src_b = scanline_even + x_start;
            src_c = src_b;
            src_d = src_a;
            break;
         case 0x0:
         default:
            src_a = scanline_even + x_start;
            src_b = src_a;
            src_c = scanline_odd  + x_start;
            src_d = src_c;
            break;
      }

      /* Populate source arrays */
      for (x_index = x_start; x_index < x_end; x_index++)
      {
         bool x_is_even = (((x_index >> 1) & 1) == 0);
         *(scanline_even + x_index) = x_is_even ? dark_color  : light_color;
         *(scanline_odd  + x_index) = x_is_even ? light_color : dark_color;
      }

      /* Fill destination array */
      for (y_index = y_start    ; y_index < y_end; y_index += 4)
         memcpy(dst + (y_index * fb_width), src_a, x_size);

      for (y_index = y_start + 1; y_index < y_end; y_index += 4)
         memcpy(dst + (y_index * fb_width), src_b, x_size);

      for (y_index = y_start + 2; y_index < y_end; y_index += 4)
         memcpy(dst + (y_index * fb_width), src_c, x_size);

      for (y_index = y_start + 3; y_index < y_end; y_index += 4)
         memcpy(dst + (y_index * fb_width), src_d, x_size);
   }
   else
   {
      uint16_t *src_a      = NULL;
      uint16_t *src_b      = NULL;
      uint16_t *dst        = data + x_start;

      /* Determine in which order the source arrays
       * should be copied */
      if ((y_start & 1) == 0)
      {
         src_a = scanline_even + x_start;
         src_b = scanline_odd  + x_start;
      }
      else
      {
         src_a = scanline_odd  + x_start;
         src_b = scanline_even + x_start;
      }

      /* Populate source arrays */
      for (x_index = x_start; x_index < x_end; x_index++)
      {
         bool x_is_even = ((x_index & 1) == 0);
         *(scanline_even + x_index) = x_is_even ? dark_color  : light_color;
         *(scanline_odd  + x_index) = x_is_even ? light_color : dark_color;
      }

      /* Fill destination array */
      for (y_index = y_start    ; y_index < y_end; y_index += 2)
         memcpy(dst + (y_index * fb_width), src_a, x_size);

      for (y_index = y_start + 1; y_index < y_end; y_index += 2)
         memcpy(dst + (y_index * fb_width), src_b, x_size);
   }
}