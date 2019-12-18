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
typedef  int /*<<< orphan*/  mntfs ;
typedef  int /*<<< orphan*/  am_nfs_handle_t ;

/* Variables and functions */
 int ENOENT ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  dlog (char*,char*,char*) ; 
 int /*<<< orphan*/  mkdirs (char*,int) ; 
 int mount_nfs_fh (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int
do_mount(am_nfs_handle_t *fhp, char *mntdir, char *fs_name, mntfs *mf)
{
  struct stat stb;

  dlog("amfs_host: mounting fs %s on %s\n", fs_name, mntdir);

  (void) mkdirs(mntdir, 0555);
  if (stat(mntdir, &stb) < 0 || (stb.st_mode & S_IFMT) != S_IFDIR) {
    plog(XLOG_ERROR, "No mount point for %s - skipping", mntdir);
    return ENOENT;
  }

  return mount_nfs_fh(fhp, mntdir, fs_name, mf);
}