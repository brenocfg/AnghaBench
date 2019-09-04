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
struct stat {int dummy; } ;

/* Variables and functions */
 int orig_stat (char const*,struct stat*) ; 

int
rpl_stat (char const *name, struct stat *st)
{
  int result = orig_stat (name, st);
#if REPLACE_FUNC_STAT_FILE
  /* Solaris 9 mistakenly succeeds when given a non-directory with a
     trailing slash.  */
  if (result == 0 && !S_ISDIR (st->st_mode))
    {
      size_t len = strlen (name);
      if (ISSLASH (name[len - 1]))
        {
          errno = ENOTDIR;
          return -1;
        }
    }
#endif /* REPLACE_FUNC_STAT_FILE */
#if REPLACE_FUNC_STAT_DIR

  if (result == -1 && errno == ENOENT)
    {
      /* Due to mingw's oddities, there are some directories (like
         c:\) where stat() only succeeds with a trailing slash, and
         other directories (like c:\windows) where stat() only
         succeeds without a trailing slash.  But we want the two to be
         synonymous, since chdir() manages either style.  Likewise, Mingw also
         reports ENOENT for names longer than PATH_MAX, when we want
         ENAMETOOLONG, and for stat("file/"), when we want ENOTDIR.
         Fortunately, mingw PATH_MAX is small enough for stack
         allocation.  */
      char fixed_name[PATH_MAX + 1] = {0};
      size_t len = strlen (name);
      bool check_dir = false;
      verify (PATH_MAX <= 4096);
      if (PATH_MAX <= len)
        errno = ENAMETOOLONG;
      else if (len)
        {
          strcpy (fixed_name, name);
          if (ISSLASH (fixed_name[len - 1]))
            {
              check_dir = true;
              while (len && ISSLASH (fixed_name[len - 1]))
                fixed_name[--len] = '\0';
              if (!len)
                fixed_name[0] = '/';
            }
          else
            fixed_name[len++] = '/';
          result = orig_stat (fixed_name, st);
          if (result == 0 && check_dir && !S_ISDIR (st->st_mode))
            {
              result = -1;
              errno = ENOTDIR;
            }
        }
    }
#endif /* REPLACE_FUNC_STAT_DIR */
  return result;
}