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

/* Variables and functions */

__attribute__((used)) static void to_lower_string( char *str )
{
   char c;

   while ((c = *str) != '\0')
   {
      if (c >= 'A' && c <= 'Z')
         *str = c - 'A' + 'a';
      str++;
   }
}