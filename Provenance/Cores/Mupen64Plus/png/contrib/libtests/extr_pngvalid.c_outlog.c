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
struct TYPE_3__ {int log8; scalar_t__ log16; scalar_t__ calculations_use_input_precision; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static double outlog(const png_modifier *pm, int in_depth, int out_depth)
{
   /* The command line parameters are either 8 bit (0..255) or 16 bit (0..65535)
    * and so must be adjusted for low bit depth grayscale:
    */
   if (out_depth <= 8)
   {
      if (pm->log8 == 0) /* switched off */
         return 256;

      if (out_depth < 8)
         return pm->log8 / 255 * ((1<<out_depth)-1);

      return pm->log8;
   }

   if ((pm->calculations_use_input_precision ? in_depth : out_depth) == 16)
   {
      if (pm->log16 == 0)
         return 65536;

      return pm->log16;
   }

   /* This is the case where the value was calculated at 8-bit precision then
    * scaled to 16 bits.
    */
   if (pm->log8 == 0)
      return 65536;

   return pm->log8 * 257;
}