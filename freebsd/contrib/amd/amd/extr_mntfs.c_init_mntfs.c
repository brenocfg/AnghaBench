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
struct TYPE_6__ {int mf_refc; int mf_error; int /*<<< orphan*/ * mf_server; int /*<<< orphan*/ * mf_prfree; int /*<<< orphan*/ * mf_private; scalar_t__ mf_cid; scalar_t__ mf_flags; int /*<<< orphan*/ * mf_loopdev; void* mf_remopts; void* mf_mopts; void* mf_auto; void* mf_info; void* mf_mount; scalar_t__ mf_fo; int /*<<< orphan*/  mf_fsflags; TYPE_2__* mf_ops; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_opts ;
struct TYPE_7__ {int /*<<< orphan*/ * (* ffserver ) (TYPE_1__*) ;int /*<<< orphan*/  nfs_fs_flags; } ;
typedef  TYPE_2__ am_ops ;

/* Variables and functions */
 scalar_t__ copy_opts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void
init_mntfs(mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts)
{
  mf->mf_ops = ops;
  mf->mf_fsflags = ops->nfs_fs_flags;
  mf->mf_fo = 0;
  if (mo)
    mf->mf_fo = copy_opts(mo);

  mf->mf_mount = xstrdup(mp);
  mf->mf_info = xstrdup(info);
  mf->mf_auto = xstrdup(auto_opts);
  mf->mf_mopts = xstrdup(mopts);
  mf->mf_remopts = xstrdup(remopts);
  mf->mf_loopdev = NULL;
  mf->mf_refc = 1;
  mf->mf_flags = 0;
  mf->mf_error = -1;
  mf->mf_cid = 0;
  mf->mf_private = NULL;
  mf->mf_prfree = NULL;

  if (ops->ffserver)
    mf->mf_server = (*ops->ffserver) (mf);
  else
    mf->mf_server = NULL;
}