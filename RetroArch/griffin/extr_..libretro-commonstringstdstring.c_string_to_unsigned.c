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
 int /*<<< orphan*/  isdigit (char const) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int) ; 

unsigned string_to_unsigned(const char *str)
{
   const char *ptr = NULL;

   if (string_is_empty(str))
      return 0;

   for (ptr = str; *ptr != '\0'; ptr++)
   {
      if (!isdigit(*ptr))
         return 0;
   }

   return (unsigned)strtoul(str, NULL, 10);
}