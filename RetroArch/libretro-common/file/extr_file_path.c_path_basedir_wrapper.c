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
 char* find_last_slash (char*) ; 
 char* path_default_slash () ; 
 scalar_t__ path_get_archive_delim (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 

void path_basedir_wrapper(char *path)
{
   char *last = NULL;
   if (strlen(path) < 2)
      return;

#ifdef HAVE_COMPRESSION
   /* We want to find the directory with the archive in basedir. */
   last = (char*)path_get_archive_delim(path);
   if (last)
      *last = '\0';
#endif

   last = find_last_slash(path);

   if (last)
      last[1] = '\0';
   else
      snprintf(path, 3, ".%s", path_default_slash());
}