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

/* Variables and functions */
 int pixel_depth_of_type (int,int) ; 

__attribute__((used)) static unsigned int
image_size_of_type(int color_type, int bit_depth, unsigned int *colors,
   int small)
{
   if (*colors)
      return 16;

   else
   {
      int pixel_depth = pixel_depth_of_type(color_type, bit_depth);

      if (small)
      {
         if (pixel_depth <= 8) /* there will be one row */
            return 1 << pixel_depth;

         else
            return 256;
      }

      else if (pixel_depth < 8)
         return 64;

      else if (pixel_depth > 16)
         return 1024;

      else
         return 256;
   }
}