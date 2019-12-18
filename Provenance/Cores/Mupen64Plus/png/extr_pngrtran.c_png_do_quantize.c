#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_row_infop ;
typedef  void** png_const_bytep ;
typedef  size_t* png_bytep ;
struct TYPE_3__ {scalar_t__ width; int bit_depth; scalar_t__ color_type; int channels; int pixel_depth; void* rowbytes; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 scalar_t__ PNG_COLOR_TYPE_RGB ; 
 scalar_t__ PNG_COLOR_TYPE_RGB_ALPHA ; 
 int PNG_QUANTIZE_BLUE_BITS ; 
 int PNG_QUANTIZE_GREEN_BITS ; 
 int PNG_QUANTIZE_RED_BITS ; 
 void* PNG_ROWBYTES (int,scalar_t__) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
png_do_quantize(png_row_infop row_info, png_bytep row,
    png_const_bytep palette_lookup, png_const_bytep quantize_lookup)
{
   png_bytep sp, dp;
   png_uint_32 i;
   png_uint_32 row_width=row_info->width;

   png_debug(1, "in png_do_quantize");

   if (row_info->bit_depth == 8)
   {
      if (row_info->color_type == PNG_COLOR_TYPE_RGB && palette_lookup)
      {
         int r, g, b, p;
         sp = row;
         dp = row;
         for (i = 0; i < row_width; i++)
         {
            r = *sp++;
            g = *sp++;
            b = *sp++;

            /* This looks real messy, but the compiler will reduce
             * it down to a reasonable formula.  For example, with
             * 5 bits per color, we get:
             * p = (((r >> 3) & 0x1f) << 10) |
             *    (((g >> 3) & 0x1f) << 5) |
             *    ((b >> 3) & 0x1f);
             */
            p = (((r >> (8 - PNG_QUANTIZE_RED_BITS)) &
                ((1 << PNG_QUANTIZE_RED_BITS) - 1)) <<
                (PNG_QUANTIZE_GREEN_BITS + PNG_QUANTIZE_BLUE_BITS)) |
                (((g >> (8 - PNG_QUANTIZE_GREEN_BITS)) &
                ((1 << PNG_QUANTIZE_GREEN_BITS) - 1)) <<
                (PNG_QUANTIZE_BLUE_BITS)) |
                ((b >> (8 - PNG_QUANTIZE_BLUE_BITS)) &
                ((1 << PNG_QUANTIZE_BLUE_BITS) - 1));

            *dp++ = palette_lookup[p];
         }

         row_info->color_type = PNG_COLOR_TYPE_PALETTE;
         row_info->channels = 1;
         row_info->pixel_depth = row_info->bit_depth;
         row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth, row_width);
      }

      else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA &&
         palette_lookup != NULL)
      {
         int r, g, b, p;
         sp = row;
         dp = row;
         for (i = 0; i < row_width; i++)
         {
            r = *sp++;
            g = *sp++;
            b = *sp++;
            sp++;

            p = (((r >> (8 - PNG_QUANTIZE_RED_BITS)) &
                ((1 << PNG_QUANTIZE_RED_BITS) - 1)) <<
                (PNG_QUANTIZE_GREEN_BITS + PNG_QUANTIZE_BLUE_BITS)) |
                (((g >> (8 - PNG_QUANTIZE_GREEN_BITS)) &
                ((1 << PNG_QUANTIZE_GREEN_BITS) - 1)) <<
                (PNG_QUANTIZE_BLUE_BITS)) |
                ((b >> (8 - PNG_QUANTIZE_BLUE_BITS)) &
                ((1 << PNG_QUANTIZE_BLUE_BITS) - 1));

            *dp++ = palette_lookup[p];
         }

         row_info->color_type = PNG_COLOR_TYPE_PALETTE;
         row_info->channels = 1;
         row_info->pixel_depth = row_info->bit_depth;
         row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth, row_width);
      }

      else if (row_info->color_type == PNG_COLOR_TYPE_PALETTE &&
         quantize_lookup)
      {
         sp = row;

         for (i = 0; i < row_width; i++, sp++)
         {
            *sp = quantize_lookup[*sp];
         }
      }
   }
}