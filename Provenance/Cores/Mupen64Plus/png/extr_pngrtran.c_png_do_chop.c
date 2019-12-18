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
typedef  TYPE_1__* png_row_infop ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  scalar_t__ png_byte ;
struct TYPE_3__ {int bit_depth; int rowbytes; int channels; int width; scalar_t__ pixel_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
/* Simply discard the low byte.  This was the default behavior prior
 * to libpng-1.5.4.
 */
png_do_chop(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_chop");

   if (row_info->bit_depth == 16)
   {
      png_bytep sp = row; /* source */
      png_bytep dp = row; /* destination */
      png_bytep ep = sp + row_info->rowbytes; /* end+1 */

      while (sp < ep)
      {
         *dp++ = *sp;
         sp += 2; /* skip low byte */
      }

      row_info->bit_depth = 8;
      row_info->pixel_depth = (png_byte)(8 * row_info->channels);
      row_info->rowbytes = row_info->width * row_info->channels;
   }
}