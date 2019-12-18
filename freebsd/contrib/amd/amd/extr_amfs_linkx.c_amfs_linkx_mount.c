#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_5__ {char* mf_mount; } ;
typedef  TYPE_1__ mntfs ;
struct TYPE_6__ {char* am_link; } ;
typedef  TYPE_2__ am_node ;

/* Variables and functions */
 int errno ; 
 scalar_t__ lstat (char*,struct stat*) ; 

__attribute__((used)) static int
amfs_linkx_mount(am_node *mp, mntfs *mf)
{
  /*
   * Check for existence of target.
   */
  struct stat stb;
  char *ln;

  if (mp->am_link)
    ln = mp->am_link;
  else				/* should never occur */
    ln = mf->mf_mount;

  /*
   * Use lstat, not stat, since we don't
   * want to know if the ultimate target of
   * a symlink chain exists, just the first.
   */
  if (lstat(ln, &stb) < 0)
    return errno;

  return 0;
}