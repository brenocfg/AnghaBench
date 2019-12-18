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

__attribute__((used)) static bool next_string(char **_ptr, char **_str)
{
   char *ptr = *_ptr;

   while (*ptr == ' ')       /* skip any spaces... */
      ptr++;

   if (*ptr == '\0')
      return false;

   while ((*ptr != ' ') && (*ptr != '\n') && (*ptr != '\0'))
      ptr++;

   if (*ptr != '\0')
      *(ptr++) = '\0';

   *_ptr = ptr;
   return true;
}