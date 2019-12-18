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
typedef  int png_uint_32 ;
typedef  int* png_const_bytep ;

/* Variables and functions */
 scalar_t__ memcmp (int*,int*,int) ; 

__attribute__((used)) static int
pixel_cmp(png_const_bytep pa, png_const_bytep pb, png_uint_32 bit_width)
{
#if PNG_LIBPNG_VER < 10506
   if (memcmp(pa, pb, bit_width>>3) == 0)
   {
      png_uint_32 p;

      if ((bit_width & 7) == 0) return 0;

      /* Ok, any differences? */
      p = pa[bit_width >> 3];
      p ^= pb[bit_width >> 3];

      if (p == 0) return 0;

      /* There are, but they may not be significant, remove the bits
       * after the end (the low order bits in PNG.)
       */
      bit_width &= 7;
      p >>= 8-bit_width;

      if (p == 0) return 0;
   }
#else
   /* From libpng-1.5.6 the overwrite should be fixed, so compare the trailing
    * bits too:
    */
   if (memcmp(pa, pb, (bit_width+7)>>3) == 0)
      return 0;
#endif

   /* Return the index of the changed byte. */
   {
      png_uint_32 where = 0;

      while (pa[where] == pb[where]) ++where;
      return 1+where;
   }
}