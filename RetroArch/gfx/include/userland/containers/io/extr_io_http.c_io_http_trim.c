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
 int strlen (char*) ; 

__attribute__((used)) static char *io_http_trim(char *str)
{
   char *s = str + strlen(str);

   /* Search backwards for first non-whitespace */
   while (--s >= str &&(*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'))
      ;     /* Everything done in the while */
   s[1] = '\0';

   /* Now move start of string forwards to first non-whitespace */
   s = str;
   while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
      s++;

   return s;
}