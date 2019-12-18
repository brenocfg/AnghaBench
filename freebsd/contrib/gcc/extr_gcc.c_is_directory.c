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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_SEPARATOR ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
is_directory (const char *path1, bool linker)
{
  int len1;
  char *path;
  char *cp;
  struct stat st;

  /* Ensure the string ends with "/.".  The resulting path will be a
     directory even if the given path is a symbolic link.  */
  len1 = strlen (path1);
  path = alloca (3 + len1);
  memcpy (path, path1, len1);
  cp = path + len1;
  if (!IS_DIR_SEPARATOR (cp[-1]))
    *cp++ = DIR_SEPARATOR;
  *cp++ = '.';
  *cp = '\0';

#ifndef FREEBSD_NATIVE
  /* Exclude directories that the linker is known to search.  */
  if (linker
      && IS_DIR_SEPARATOR (path[0])
      && ((cp - path == 6
	   && strncmp (path + 1, "lib", 3) == 0)
	  || (cp - path == 10
	      && strncmp (path + 1, "usr", 3) == 0
	      && IS_DIR_SEPARATOR (path[4])
	      && strncmp (path + 5, "lib", 3) == 0)))
    return 0;
#endif /* FREEBSD_NATIVE */

  return (stat (path, &st) >= 0 && S_ISDIR (st.st_mode));
}