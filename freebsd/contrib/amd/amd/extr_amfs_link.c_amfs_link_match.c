#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* opt_fs; char* opt_sublink; } ;
typedef  TYPE_1__ am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 char* str3cat (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* xstrdup (char*) ; 

char *
amfs_link_match(am_opts *fo)
{

  if (!fo->opt_fs) {
    plog(XLOG_USER, "link: no fs specified");
    return 0;
  }

  /*
   * If the link target points to another mount point, then we could
   * end up with an unpleasant situation, where the link f/s simply
   * "assumes" the mntfs of that mount point.
   *
   * For example, if the link points to /usr, and /usr is a real ufs
   * filesystem, then the link f/s will use the inherited ufs mntfs,
   * and the end result will be that it will become unmountable.
   *
   * To prevent this, we use a hack: we prepend a dot ('.') to opt_fs if
   * its original value was an absolute path, so that it will never match
   * any other mntfs.
   *
   * XXX: a less hacky solution should be used...
   */
  if (fo->opt_fs[0] == '/') {
    char *link_hack = str3cat(NULL, ".", fo->opt_fs, "");
    if (fo->opt_sublink == NULL || fo->opt_sublink[0] == '\0')
      fo->opt_sublink = xstrdup(fo->opt_fs);
    XFREE(fo->opt_fs);
    fo->opt_fs = link_hack;
  }

  return xstrdup(fo->opt_fs);
}