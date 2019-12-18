#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int png_size_t ;
typedef  TYPE_1__* png_row_infop ;
typedef  TYPE_2__* png_const_colorp ;
typedef  int /*<<< orphan*/ * png_const_bytep ;
typedef  int* png_bytep ;
typedef  int png_byte ;
struct TYPE_6__ {int /*<<< orphan*/  red; int /*<<< orphan*/  green; int /*<<< orphan*/  blue; } ;
struct TYPE_5__ {int width; int color_type; int bit_depth; int pixel_depth; int rowbytes; int channels; } ;

/* Variables and functions */
 int PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
png_do_expand_palette(png_row_infop row_info, png_bytep row,
    png_const_colorp palette, png_const_bytep trans_alpha, int num_trans)
{
   int shift, value;
   png_bytep sp, dp;
   png_uint_32 i;
   png_uint_32 row_width=row_info->width;

   png_debug(1, "in png_do_expand_palette");

   if (row_info->color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (row_info->bit_depth < 8)
      {
         switch (row_info->bit_depth)
         {
            case 1:
            {
               sp = row + (png_size_t)((row_width - 1) >> 3);
               dp = row + (png_size_t)row_width - 1;
               shift = 7 - (int)((row_width + 7) & 0x07);
               for (i = 0; i < row_width; i++)
               {
                  if ((*sp >> shift) & 0x01)
                     *dp = 1;

                  else
                     *dp = 0;

                  if (shift == 7)
                  {
                     shift = 0;
                     sp--;
                  }

                  else
                     shift++;

                  dp--;
               }
               break;
            }

            case 2:
            {
               sp = row + (png_size_t)((row_width - 1) >> 2);
               dp = row + (png_size_t)row_width - 1;
               shift = (int)((3 - ((row_width + 3) & 0x03)) << 1);
               for (i = 0; i < row_width; i++)
               {
                  value = (*sp >> shift) & 0x03;
                  *dp = (png_byte)value;
                  if (shift == 6)
                  {
                     shift = 0;
                     sp--;
                  }

                  else
                     shift += 2;

                  dp--;
               }
               break;
            }

            case 4:
            {
               sp = row + (png_size_t)((row_width - 1) >> 1);
               dp = row + (png_size_t)row_width - 1;
               shift = (int)((row_width & 0x01) << 2);
               for (i = 0; i < row_width; i++)
               {
                  value = (*sp >> shift) & 0x0f;
                  *dp = (png_byte)value;
                  if (shift == 4)
                  {
                     shift = 0;
                     sp--;
                  }

                  else
                     shift += 4;

                  dp--;
               }
               break;
            }

            default:
               break;
         }
         row_info->bit_depth = 8;
         row_info->pixel_depth = 8;
         row_info->rowbytes = row_width;
      }

      if (row_info->bit_depth == 8)
      {
         {
            if (num_trans > 0)
            {
               sp = row + (png_size_t)row_width - 1;
               dp = row + (png_size_t)(row_width << 2) - 1;

               for (i = 0; i < row_width; i++)
               {
                  if ((int)(*sp) >= num_trans)
                     *dp-- = 0xff;

                  else
                     *dp-- = trans_alpha[*sp];

                  *dp-- = palette[*sp].blue;
                  *dp-- = palette[*sp].green;
                  *dp-- = palette[*sp].red;
                  sp--;
               }
               row_info->bit_depth = 8;
               row_info->pixel_depth = 32;
               row_info->rowbytes = row_width * 4;
               row_info->color_type = 6;
               row_info->channels = 4;
            }

            else
            {
               sp = row + (png_size_t)row_width - 1;
               dp = row + (png_size_t)(row_width * 3) - 1;

               for (i = 0; i < row_width; i++)
               {
                  *dp-- = palette[*sp].blue;
                  *dp-- = palette[*sp].green;
                  *dp-- = palette[*sp].red;
                  sp--;
               }

               row_info->bit_depth = 8;
               row_info->pixel_depth = 24;
               row_info->rowbytes = row_width * 3;
               row_info->color_type = 2;
               row_info->channels = 3;
            }
         }
      }
   }
}