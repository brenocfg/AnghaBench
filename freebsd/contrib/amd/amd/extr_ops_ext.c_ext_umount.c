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
struct TYPE_3__ {int mf_flags; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int AMU_UMOUNT_AUTOFS ; 
 int MFF_ON_AUTOFS ; 
 int UMOUNT_FS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 

__attribute__((used)) static int
ext_umount(am_node *am, mntfs *mf)
{
  int unmount_flags = (mf->mf_flags & MFF_ON_AUTOFS) ? AMU_UMOUNT_AUTOFS : 0;

  return UMOUNT_FS(mf->mf_mount, mnttab_file_name, unmount_flags);
}