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
 scalar_t__ string_is_empty (char*) ; 

void string_remove_all_chars(char *str, char c)
{
   char *read_ptr  = NULL;
   char *write_ptr = NULL;

   if (string_is_empty(str))
      return;

   read_ptr  = str;
   write_ptr = str;

   while (*read_ptr != '\0')
   {
      *write_ptr = *read_ptr++;
      write_ptr += (*write_ptr != c) ? 1 : 0;
   }

   *write_ptr = '\0';
}