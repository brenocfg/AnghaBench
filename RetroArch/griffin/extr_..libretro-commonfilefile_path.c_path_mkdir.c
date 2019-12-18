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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ path_is_directory (char const*) ; 
 int path_mkdir_cb (char const*) ; 
 int /*<<< orphan*/  path_parent_dir (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 

bool path_mkdir(const char *dir)
{
   bool         sret  = false;
   bool norecurse     = false;
   char     *basedir  = NULL;

   if (!(dir && *dir))
      return false;

   /* Use heap. Real chance of stack 
    * overflow if we recurse too hard. */
   basedir            = strdup(dir);

   if (!basedir)
	   return false;

   path_parent_dir(basedir);

   if (!*basedir || !strcmp(basedir, dir))
   {
      free(basedir);
      return false;
   }

#if defined(GEKKO)
   {
      size_t len = strlen(basedir);

      /* path_parent_dir() keeps the trailing slash.
       * On Wii, mkdir() fails if the path has a
       * trailing slash...
       * We must therefore remove it. */
      if (len > 0)
         if (basedir[len - 1] == '/')
            basedir[len - 1] = '\0';
   }
#endif

   if (path_is_directory(basedir))
      norecurse = true;
   else
   {
      sret      = path_mkdir(basedir);

      if (sret)
         norecurse = true;
   }

   free(basedir);

   if (norecurse)
   {
      int ret = path_mkdir_cb(dir);

      /* Don't treat this as an error. */
      if (ret == -2 && path_is_directory(dir))
         return true;

      return (ret == 0);
   }

   return sret;
}