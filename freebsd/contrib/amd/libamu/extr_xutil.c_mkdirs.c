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
struct stat {int st_mode; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 int errno ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 char* xstrdup (char*) ; 

int
mkdirs(char *path, int mode)
{
  /*
   * take a copy in case path is in readonly store
   */
  char *p2 = xstrdup(path);
  char *sp = p2;
  struct stat stb;
  int error_so_far = 0;

  /*
   * Skip through the string make the directories.
   * Mostly ignore errors - the result is tested at the end.
   *
   * This assumes we are root so that we can do mkdir in a
   * mode 555 directory...
   */
  while ((sp = strchr(sp + 1, '/'))) {
    *sp = '\0';
    if (mkdir(p2, mode) < 0) {
      error_so_far = errno;
    } else {
      dlog("mkdir(%s)", p2);
    }
    *sp = '/';
  }

  if (mkdir(p2, mode) < 0) {
    error_so_far = errno;
  } else {
    dlog("mkdir(%s)", p2);
  }

  XFREE(p2);

  return stat(path, &stb) == 0 &&
    (stb.st_mode & S_IFMT) == S_IFDIR ? 0 : error_so_far;
}