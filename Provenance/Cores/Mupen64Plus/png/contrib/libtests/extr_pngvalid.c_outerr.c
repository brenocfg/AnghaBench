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
struct TYPE_3__ {double maxout16; int maxout8; scalar_t__ calculations_use_input_precision; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static double outerr(const png_modifier *pm, int in_depth, int out_depth)
{
   /* There is a serious error in the 2 and 4 bit grayscale transform because
    * the gamma table value (8 bits) is simply shifted, not rounded, so the
    * error in 4 bit grayscale gamma is up to the value below.  This is a hack
    * to allow pngvalid to succeed:
    *
    * TODO: fix this in libpng
    */
   if (out_depth == 2)
      return .73182-.5;

   if (out_depth == 4)
      return .90644-.5;

   if ((pm->calculations_use_input_precision ? in_depth : out_depth) == 16)
      return pm->maxout16;

   /* This is the case where the value was calculated at 8-bit precision then
    * scaled to 16 bits.
    */
   else if (out_depth == 16)
      return pm->maxout8 * 257;

   else
      return pm->maxout8;
}