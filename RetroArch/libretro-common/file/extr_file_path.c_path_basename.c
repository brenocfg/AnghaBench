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
 char* find_last_slash (char const*) ; 
 char* path_get_archive_delim (char const*) ; 

const char *path_basename(const char *path)
{
   /* We cut at the first compression-related hash */
   const char *delim = path_get_archive_delim(path);
   if (delim)
      return delim + 1;

   {
      /* We cut at the last slash */
      const char *last  = find_last_slash(path);
      if (last)
         return last + 1;
   }

   return path;
}