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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int from_hex (char const*,int) ; 

__attribute__((used)) static void unescape_string( const char *str, uint32_t str_len, char *unescaped )
{
   uint32_t ii;

   for (ii = 0; ii < str_len; ii++)
   {
      char c = *str++;

      if (c == '%' && (ii + 2) < str_len )
      {
         c = (char)(from_hex(str, 2) & 0xFF);
         str += 2;
         ii += 2;
      }
      *unescaped++ = c;
   }

   *unescaped = '\0';
}