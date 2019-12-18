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
 int utf8_walkbyte (char const**) ; 

uint32_t utf8_walk(const char **string)
{
   uint8_t first = utf8_walkbyte(string);
   uint32_t ret  = 0;

   if (first < 128)
      return first;

   ret    = (ret << 6) | (utf8_walkbyte(string) & 0x3F);
   if (first >= 0xE0)
   {
      ret = (ret << 6) | (utf8_walkbyte(string) & 0x3F);
      if (first >= 0xF0)
      {
         ret = (ret << 6) | (utf8_walkbyte(string) & 0x3F);
         return ret | (first & 7) << 18;
      }
      return ret | (first & 15) << 12;
   }

   return ret | (first & 31) << 6;
}