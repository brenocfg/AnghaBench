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
struct file_archive_file_backend {int dummy; } ;
typedef  int /*<<< orphan*/  newpath ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 scalar_t__ path_get_archive_delim (char*) ; 
 char* path_get_extension (char*) ; 
 struct file_archive_file_backend const sevenzip_backend ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 struct file_archive_file_backend const zlib_backend ; 

const struct file_archive_file_backend* file_archive_get_file_backend(const char *path)
{
#if defined(HAVE_7ZIP) || defined(HAVE_ZLIB)
   char newpath[PATH_MAX_LENGTH];
   const char *file_ext          = NULL;
   char *last                    = NULL;

   newpath[0] = '\0';

   strlcpy(newpath, path, sizeof(newpath));

   last = (char*)path_get_archive_delim(newpath);

   if (last)
      *last = '\0';

   file_ext = path_get_extension(newpath);

#ifdef HAVE_7ZIP
   if (string_is_equal_noncase(file_ext, "7z"))
      return &sevenzip_backend;
#endif

#ifdef HAVE_ZLIB
   if (     string_is_equal_noncase(file_ext, "zip")
         || string_is_equal_noncase(file_ext, "apk")
      )
      return &zlib_backend;
#endif
#endif

   return NULL;
}