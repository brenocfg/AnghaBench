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
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void get_old_format_metadata_value(
      char *metadata_line, char *value, size_t len)
{
   char *start = NULL;
   char *end   = NULL;

   start = strchr(metadata_line, '\"');

   if (!start)
      return;

   start++;
   end = strchr(start, '\"');

   if (!end)
      return;

   *end = '\0';
   strlcpy(value, start, len);
}