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
struct TYPE_3__ {unsigned int ngammas; unsigned int nencodings; int bit_depth; scalar_t__ assume_16_bit_calculations; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static unsigned int
modifier_total_encodings(const png_modifier *pm)
{
   return 1 +                 /* (1) nothing */
      pm->ngammas +           /* (2) gamma values to test */
      pm->nencodings +        /* (3) total number of encodings */
      /* The following test only works after the first time through the
       * png_modifier code because 'bit_depth' is set when the IHDR is read.
       * modifier_reset, below, preserves the setting until after it has called
       * the iterate function (also below.)
       *
       * For this reason do not rely on this function outside a call to
       * modifier_reset.
       */
      ((pm->bit_depth == 16 || pm->assume_16_bit_calculations) ?
         pm->nencodings : 0); /* (4) encodings with gamma == 1.0 */
}