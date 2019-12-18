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
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  int /*<<< orphan*/  png_const_structrp ;

/* Variables and functions */
 scalar_t__ png_muldiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ ,char*) ; 

png_fixed_point
png_muldiv_warn(png_const_structrp png_ptr, png_fixed_point a, png_int_32 times,
    png_int_32 divisor)
{
   png_fixed_point result;

   if (png_muldiv(&result, a, times, divisor) != 0)
      return result;

   png_warning(png_ptr, "fixed point overflow ignored");
   return 0;
}