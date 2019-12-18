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
typedef  scalar_t__* uarb ;
typedef  scalar_t__ png_uint_16 ;
typedef  int png_alloc_size_t ;

/* Variables and functions */

__attribute__((used)) static int
uarb_set(uarb result, png_alloc_size_t val)
   /* Set (initialize) 'result' to 'val'.  The size required for 'result' must
    * be determined by the caller from a knowledge of the maximum for 'val'.
    */
{
   int ndigits = 0;

   while (val > 0)
   {
      result[ndigits++] = (png_uint_16)(val & 0xffff);
      val >>= 16;
   }

   return ndigits;
}