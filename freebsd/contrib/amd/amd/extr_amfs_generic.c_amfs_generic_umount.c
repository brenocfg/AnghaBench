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
struct TYPE_5__ {int mf_flags; } ;
typedef  TYPE_1__ mntfs ;
struct TYPE_6__ {int /*<<< orphan*/  am_path; } ;
typedef  TYPE_2__ am_node ;

/* Variables and functions */
 int AMU_UMOUNT_AUTOFS ; 
 int MFF_IS_AUTOFS ; 
 int MFF_ON_AUTOFS ; 
 int UMOUNT_FS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 

int
amfs_generic_umount(am_node *mp, mntfs *mf)
{
  int error = 0;

#ifdef HAVE_FS_AUTOFS
  int unmount_flags = (mf->mf_flags & MFF_ON_AUTOFS) ? AMU_UMOUNT_AUTOFS : 0;
  if (mf->mf_flags & MFF_IS_AUTOFS)
    error = UMOUNT_FS(mp->am_path, mnttab_file_name, unmount_flags);
#endif /* HAVE_FS_AUTOFS */

  return error;
}