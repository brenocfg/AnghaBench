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
 void* find_last_slash (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

bool fill_pathname_parent_dir_name(char *out_dir,
      const char *in_dir, size_t size)
{
   bool success = false;
   char *temp   = strdup(in_dir);
   char *last   = find_last_slash(temp);

   if (last && last[1] == 0)
   {
      *last     = '\0';
      last      = find_last_slash(temp);
   }

   if (last)
      *last     = '\0';

   in_dir       = find_last_slash(temp);

   success      = in_dir && in_dir[1];

   if (success)
      strlcpy(out_dir, in_dir + 1, size);

   free(temp);
   return success;
}