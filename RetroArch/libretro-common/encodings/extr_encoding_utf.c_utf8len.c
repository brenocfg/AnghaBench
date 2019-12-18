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

size_t utf8len(const char *string)
{
   size_t ret = 0;

   if (!string)
      return 0;

   while (*string)
   {
      if ((*string & 0xC0) != 0x80)
         ret++;
      string++;
   }
   return ret;
}