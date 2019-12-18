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

/* Variables and functions */

__attribute__((used)) static int
valid_chunktype(png_uint_32 chunktype)
{
   /* Each byte in the chunk type must be in one of the ranges 65..90, 97..122
    * (both inclusive), so:
    */
   unsigned int i;

   for (i=0; i<4; ++i)
   {
      unsigned int c = chunktype & 0xffU;

      if (!((c >= 65U && c <= 90U) || (c >= 97U && c <= 122U)))
         return 0;

      chunktype >>= 8;
   }

   return 1; /* It's valid */
}