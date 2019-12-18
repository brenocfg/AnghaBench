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
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;
struct TYPE_3__ {int bit_depth; scalar_t__ color_type; int rowbytes; int channels; scalar_t__ pixel_depth; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 

__attribute__((used)) static void
png_do_expand_16(png_row_infop row_info, png_bytep row)
{
   if (row_info->bit_depth == 8 &&
      row_info->color_type != PNG_COLOR_TYPE_PALETTE)
   {
      /* The row have a sequence of bytes containing [0..255] and we need
       * to turn it into another row containing [0..65535], to do this we
       * calculate:
       *
       *  (input / 255) * 65535
       *
       *  Which happens to be exactly input * 257 and this can be achieved
       *  simply by byte replication in place (copying backwards).
       */
      png_byte *sp = row + row_info->rowbytes; /* source, last byte + 1 */
      png_byte *dp = sp + row_info->rowbytes;  /* destination, end + 1 */
      while (dp > sp)
         dp[-2] = dp[-1] = *--sp, dp -= 2;

      row_info->rowbytes *= 2;
      row_info->bit_depth = 16;
      row_info->pixel_depth = (png_byte)(row_info->channels * 16);
   }
}