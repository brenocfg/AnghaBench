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

/* Variables and functions */

const char *utf8skip(const char *str, size_t chars)
{
   const uint8_t *strb = (const uint8_t*)str;
   if (!chars)
      return str;
   do
   {
      strb++;
      while ((*strb & 0xC0)==0x80) strb++;
      chars--;
   } while(chars);
   return (const char*)strb;
}