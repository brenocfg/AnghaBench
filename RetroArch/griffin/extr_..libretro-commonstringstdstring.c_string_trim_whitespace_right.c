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
 scalar_t__ isspace (unsigned char) ; 
 size_t strlen (char* const) ; 

char *string_trim_whitespace_right(char *const s)
{
   if(s && *s)
   {
      size_t len     = strlen(s);
      char  *current = s + len - 1;

      while(current != s && isspace((unsigned char)*current))
      {
         --current;
         --len;
      }

      current[isspace((unsigned char)*current) ? 0 : 1] = '\0';
   }

   return s;
}