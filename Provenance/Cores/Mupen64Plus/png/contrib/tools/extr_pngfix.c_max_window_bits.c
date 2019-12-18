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
typedef  int* uarbc ;
typedef  int png_uint_16 ;

/* Variables and functions */

__attribute__((used)) static int
max_window_bits(uarbc size, int ndigits)
   /* Return the zlib stream window bits required for data of the given size. */
{
   png_uint_16 cb;

   if (ndigits > 1)
      return 15;

   cb = size[0];

   if (cb > 16384) return 15;
   if (cb >  8192) return 14;
   if (cb >  4096) return 13;
   if (cb >  2048) return 12;
   if (cb >  1024) return 11;
   if (cb >   512) return 10;
   if (cb >   256) return  9;
   return 8;
}