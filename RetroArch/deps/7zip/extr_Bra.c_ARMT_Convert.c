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
typedef  int uint32_t ;

/* Variables and functions */

size_t ARMT_Convert(uint8_t *data, size_t size, uint32_t ip, int encoding)
{
   size_t i;
   if (size < 4)
      return 0;
   size -= 4;
   ip += 4;
   for (i = 0; i <= size; i += 2)
   {
      if ((data[i + 1] & 0xF8) == 0xF0 &&
            (data[i + 3] & 0xF8) == 0xF8)
      {
         uint32_t dest;
         uint32_t src =
            (((uint32_t)data[i + 1] & 0x7) << 19) |
            ((uint32_t)data[i + 0] << 11) |
            (((uint32_t)data[i + 3] & 0x7) << 8) |
            (data[i + 2]);

         src <<= 1;
         if (encoding)
            dest = ip + (uint32_t)i + src;
         else
            dest = src - (ip + (uint32_t)i);
         dest >>= 1;

         data[i + 1] = (uint8_t)(0xF0 | ((dest >> 19) & 0x7));
         data[i + 0] = (uint8_t)(dest >> 11);
         data[i + 3] = (uint8_t)(0xF8 | ((dest >> 8) & 0x7));
         data[i + 2] = (uint8_t)dest;
         i += 2;
      }
   }
   return i;
}