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
 int /*<<< orphan*/  memmove (char* const,char*,size_t) ; 
 size_t strlen (char* const) ; 

char *string_trim_whitespace_left(char *const s)
{
   if(s && *s)
   {
      size_t len     = strlen(s);
      char *current  = s;

      while(*current && isspace((unsigned char)*current))
      {
         ++current;
         --len;
      }

      if(s != current)
         memmove(s, current, len + 1);
   }

   return s;
}