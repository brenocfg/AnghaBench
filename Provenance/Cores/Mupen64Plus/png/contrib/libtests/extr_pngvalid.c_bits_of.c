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

__attribute__((used)) static unsigned int
bits_of(png_uint_32 num)
{
   /* Return the number of bits in 'num' */
   unsigned int b = 0;

   if (num & 0xffff0000U)  b += 16U, num >>= 16;
   if (num & 0xff00U)      b += 8U, num >>= 8;
   if (num & 0xf0U)        b += 4U, num >>= 4;
   if (num & 0xcU)         b += 2U, num >>= 2;
   if (num & 0x2U)         ++b, num >>= 1;
   if (num)                ++b;

   return b; /* 0..32 */
}