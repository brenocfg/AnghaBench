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
struct TYPE_3__ {double maxpc16; double maxpc8; scalar_t__ calculations_use_input_precision; scalar_t__ assume_16_bit_calculations; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static double pcerr(const png_modifier *pm, int in_depth, int out_depth)
{
   /* Percentage error permitted in the linear values.  Note that the specified
    * value is a percentage but this routine returns a simple number.
    */
   if (pm->assume_16_bit_calculations ||
      (pm->calculations_use_input_precision ? in_depth : out_depth) == 16)
      return pm->maxpc16 * .01;
   else
      return pm->maxpc8 * .01;
}