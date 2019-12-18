#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ opaque_t ;
struct TYPE_11__ {int mf_flags; TYPE_1__* mf_ops; } ;
typedef  TYPE_3__ mntfs ;
struct TYPE_12__ {int am_flags; int /*<<< orphan*/  am_path; TYPE_2__* am_al; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_10__ {TYPE_3__* al_mnt; } ;
struct TYPE_9__ {int (* mount_fs ) (TYPE_4__*,TYPE_3__*) ;} ;

/* Variables and functions */
 int AMF_AUTOFS ; 
 int MFF_MOUNTED ; 
 int autofs_mount_fs (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int stub1 (TYPE_4__*,TYPE_3__*) ; 

int
mount_node(opaque_t arg)
{
  am_node *mp = (am_node *) arg;
  mntfs *mf = mp->am_al->al_mnt;
  int error = 0;

#ifdef HAVE_FS_AUTOFS
  if (mp->am_flags & AMF_AUTOFS)
    error = autofs_mount_fs(mp, mf);
  else
#endif /* HAVE_FS_AUTOFS */
    if (!(mf->mf_flags & MFF_MOUNTED))
      error = mf->mf_ops->mount_fs(mp, mf);

  if (error > 0)
    dlog("mount_node: call to mf_ops->mount_fs(%s) failed: %s",
	 mp->am_path, strerror(error));
  return error;
}