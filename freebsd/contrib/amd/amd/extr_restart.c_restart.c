#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* mnt; struct TYPE_6__* mnext; } ;
typedef  TYPE_1__ mntlist ;
struct TYPE_7__ {int /*<<< orphan*/  mnt_type; int /*<<< orphan*/  mnt_fsname; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  am_ops ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTAB_TYPE_NFS ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amfs_link_ops ; 
 int /*<<< orphan*/  free_mntlist (TYPE_1__*) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int /*<<< orphan*/ * ops_search (int /*<<< orphan*/ ) ; 
 TYPE_1__* read_mtab (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restart_fake_mntfs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strstr (char*,char*) ; 

void
restart(void)
{
  mntlist *ml, *mlp;

  /*
   * Read the existing mount table.  For each entry, find nfs, ufs or auto
   * mounts and create a partial am_node to represent it.
   */
  for (mlp = ml = read_mtab("restart", mnttab_file_name);
       mlp;
       mlp = mlp->mnext) {
    mntent_t *me = mlp->mnt;
    am_ops *fs_ops = NULL;

    if (STREQ(me->mnt_type, MNTTAB_TYPE_NFS)) {
      /*
       * NFS entry, or possibly an Amd entry...
       * The mnt_fsname for daemon mount points is
       * 	host:(pidXXX)
       * or (seen on Solaris)
       *        host:daemon(pidXXX)
       */
      char *colon = strchr(me->mnt_fsname, ':');
      if (colon && strstr(colon, "(pid"))
	continue;
    }

    /* Search for the correct filesystem ops */
    fs_ops = ops_search(me->mnt_type);

    /*
     * Catch everything else with symlinks to
     * avoid recursive mounts.  This is debatable...
     */
    if (!fs_ops)
      fs_ops = &amfs_link_ops;

    restart_fake_mntfs(me, fs_ops);
  }

  /*
   * Free the mount list
   */
  free_mntlist(ml);
}