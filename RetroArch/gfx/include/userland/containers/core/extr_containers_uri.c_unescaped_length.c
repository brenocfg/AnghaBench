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

__attribute__((used)) static uint32_t unescaped_length( const char *str, uint32_t str_len )
{
   uint32_t ii;
   uint32_t unesclen = 0;

   for (ii = 0; ii < str_len; ii++)
   {
      if (*str++ == '%' && (ii + 2) < str_len)
      {
         str += 2;  /* Should be two hex values next */
         ii += 2;
      }
      unesclen++;
   }

   return unesclen;
}