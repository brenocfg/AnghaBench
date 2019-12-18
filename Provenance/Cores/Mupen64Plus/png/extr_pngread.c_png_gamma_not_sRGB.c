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
 int PNG_FP_1 ; 
 int png_gamma_significant (int) ; 

__attribute__((used)) static int
png_gamma_not_sRGB(png_fixed_point g)
{
   if (g < PNG_FP_1)
   {
      /* An uninitialized gamma is assumed to be sRGB for the simplified API. */
      if (g == 0)
         return 0;

      return png_gamma_significant((g * 11 + 2)/5 /* i.e. *2.2, rounded */);
   }

   return 1;
}