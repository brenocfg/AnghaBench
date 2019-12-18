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
 int /*<<< orphan*/  find_last_slash (char*) ; 
 int /*<<< orphan*/  path_basedir (char*) ; 
 scalar_t__ path_char_is_slash (char) ; 
 int path_is_absolute (char*) ; 
 size_t strlen (char*) ; 

void path_parent_dir(char *path)
{
   size_t len = 0;

   if (!path)
      return;
   
   len = strlen(path);

   if (len && path_char_is_slash(path[len - 1]))
   {
      bool path_was_absolute = path_is_absolute(path);

      path[len - 1] = '\0';

      if (path_was_absolute && !find_last_slash(path))
      {
         /* We removed the only slash from what used to be an absolute path.
          * On Linux, this goes from "/" to an empty string and everything works fine,
          * but on Windows, we went from C:\ to C:, which is not a valid path and that later
          * gets errornously treated as a relative one by path_basedir and returns "./".
          * What we really wanted is an empty string. */
         path[0] = '\0';
         return;
      }
   }
   path_basedir(path);
}