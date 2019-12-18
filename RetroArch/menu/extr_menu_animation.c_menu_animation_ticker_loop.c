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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static void menu_animation_ticker_loop(uint64_t idx,
      size_t max_width, size_t str_width, size_t spacer_width,
      size_t *offset1, size_t *width1,
      size_t *offset2, size_t *width2,
      size_t *offset3, size_t *width3)
{
   int ticker_period     = (int)(str_width + spacer_width);
   int phase             = idx % ticker_period;
   
   /* Output offsets/widths are unsigned size_t, but it's
    * easier to perform the required calculations with ints,
    * so create some temporary variables... */
   int offset;
   int width;
   
   /* Looping text is composed of up to three strings,
    * where string 1 and 2 are different regions of the
    * source text and string 2 is a spacer:
    * 
    *     |-----max_width-----|
    * [string 1][string 2][string 3]
    * 
    * The following implementation could probably be optimised,
    * but any performance gains would be trivial compared with
    * all the string manipulation that has to happen afterwards...
    */
   
   /* String 1 */
   offset   = (phase < (int)str_width) ? phase : 0;
   width    = (int)(str_width - phase);
   width    = (width < 0) ? 0 : width;
   width    = (width > (int)max_width) ? (int)max_width : width;
   
   *offset1 = offset;
   *width1  = width;
   
   /* String 2 */
   offset   = (int)(phase - str_width);
   offset   = offset < 0 ? 0 : offset;
   width    = (int)(max_width - *width1);
   width    = (width > (int)spacer_width) ? (int)spacer_width : width;
   width    = width - offset;
   
   *offset2 = offset;
   *width2  = width;
   
   /* String 3 */
   width    = (int)(max_width - (*width1 + *width2));
   width    = width < 0 ? 0 : width;
   
   /* Note: offset is always zero here so offset3 is
    * unnecessary - but include it anyway to preserve
    * symmetry... */
   *offset3 = 0;
   *width3  = width;
}