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
 scalar_t__ EBUSY ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOTEMPTY ; 
 scalar_t__ EROFS ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ rmdir (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (char*) ; 

void
rmdirs(char *dir)
{
  char *xdp = xstrdup(dir);
  char *dp;

  do {
    struct stat stb;
    /*
     * Try to find out whether this was
     * created by amd.  Do this by checking
     * for owner write permission.
     */
    if (stat(xdp, &stb) == 0 && (stb.st_mode & 0200) == 0) {
      if (rmdir(xdp) < 0) {
	if (errno != ENOTEMPTY &&
	    errno != EBUSY &&
	    errno != EEXIST &&
	    errno != EROFS &&
	    errno != EINVAL)
	  plog(XLOG_ERROR, "rmdir(%s): %m", xdp);
	break;
      } else {
	dlog("rmdir(%s)", xdp);
      }
    } else {
      break;
    }

    dp = strrchr(xdp, '/');
    if (dp)
      *dp = '\0';
  } while (dp && dp > xdp);

  XFREE(xdp);
}