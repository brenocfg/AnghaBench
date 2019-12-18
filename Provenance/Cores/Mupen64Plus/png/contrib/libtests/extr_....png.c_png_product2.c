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
typedef  int png_fixed_point ;

/* Variables and functions */
 double floor (double) ; 
 scalar_t__ png_muldiv (int*,int,int,int) ; 

__attribute__((used)) static png_fixed_point
png_product2(png_fixed_point a, png_fixed_point b)
{
   /* The required result is 1/a * 1/b; the following preserves accuracy. */
#ifdef PNG_FLOATING_ARITHMETIC_SUPPORTED
   double r = a * 1E-5;
   r *= b;
   r = floor(r+.5);

   if (r <= 2147483647. && r >= -2147483648.)
      return (png_fixed_point)r;
#else
   png_fixed_point res;

   if (png_muldiv(&res, a, b, 100000) != 0)
      return res;
#endif

   return 0; /* overflow */
}