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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t from_hex(const char *str, uint32_t str_len)
{
   uint32_t val = 0;

   while (str_len--)
   {
      char c = *str++;
      if (c >= '0' && c <= '9')
         c -= '0';
      else if (c >= 'A' && c <= 'F')
         c -= 'A' - 10;
      else if (c >= 'a' && c <= 'f')
         c -= 'a' - 10;
      else
         c = 0;   /* Illegal character (not hex) */
      val = (val << 4) + c;
   }

   return val;
}