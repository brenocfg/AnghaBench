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
 scalar_t__ string_is_equal_fast (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_to_upper (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool left_exclusion(char *left,
      const char **strings, const size_t strings_count)
{
   unsigned i;
   char exclusion_string[32];
   char comparison_string[32];

   strlcpy(exclusion_string, left, 32);
   string_to_upper(exclusion_string);

   for (i = 0; i < (unsigned)strings_count; i++)
   {
      strlcpy(comparison_string, strings[i], 32);
      string_to_upper(comparison_string);

      if (string_is_equal_fast(exclusion_string,
               comparison_string, strlen(comparison_string)))
         return true;
   }

   return false;
}