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
 scalar_t__ isspace (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *rtsp_trim( char *str )
{
   char *trim = str + strlen(str);

   /* Search backwards for first non-whitespace */
   while (--trim >= str && isspace((int)*trim))
      ;     /* Everything done in the while */
   trim[1] = '\0';

   /* Now move start of string forwards to first non-whitespace */
   trim = str;
   while (isspace((int)*trim))
      trim++;

   return trim;
}