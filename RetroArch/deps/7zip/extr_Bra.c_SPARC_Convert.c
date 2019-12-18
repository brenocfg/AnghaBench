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
typedef  int uint8_t ;
typedef  size_t uint32_t ;

/* Variables and functions */

size_t SPARC_Convert(uint8_t *data, size_t size, uint32_t ip, int encoding)
{
   uint32_t i;
   if (size < 4)
      return 0;
   size -= 4;
   for (i = 0; i <= size; i += 4)
   {
      if ((data[i] == 0x40 && (data[i + 1] & 0xC0) == 0x00) ||
            (data[i] == 0x7F && (data[i + 1] & 0xC0) == 0xC0))
      {
         uint32_t src =
            ((uint32_t)data[i + 0] << 24) |
            ((uint32_t)data[i + 1] << 16) |
            ((uint32_t)data[i + 2] << 8) |
            ((uint32_t)data[i + 3]);
         uint32_t dest;

         src <<= 2;
         if (encoding)
            dest = ip + i + src;
         else
            dest = src - (ip + i);
         dest >>= 2;

         dest = (((0 - ((dest >> 22) & 1)) << 22) & 0x3FFFFFFF) | (dest & 0x3FFFFF) | 0x40000000;

         data[i + 0] = (uint8_t)(dest >> 24);
         data[i + 1] = (uint8_t)(dest >> 16);
         data[i + 2] = (uint8_t)(dest >> 8);
         data[i + 3] = (uint8_t)dest;
      }
   }
   return i;
}