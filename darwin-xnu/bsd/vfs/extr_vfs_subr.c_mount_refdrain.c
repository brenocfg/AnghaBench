#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mount_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tqh_first; } ;
struct TYPE_5__ {int mnt_lflag; TYPE_1__ mnt_vnodelist; int /*<<< orphan*/  mnt_mlock; scalar_t__ mnt_count; } ;

/* Variables and functions */
 int MNT_LDRAIN ; 
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

int 
mount_refdrain(mount_t mp)
{
	if (mp->mnt_lflag & MNT_LDRAIN)
		panic("already in drain");
	mp->mnt_lflag |= MNT_LDRAIN;

	while (mp->mnt_count)
		msleep((caddr_t)&mp->mnt_lflag, &mp->mnt_mlock, PVFS, "mount_drain", NULL);

	if (mp->mnt_vnodelist.tqh_first != NULL)
		 panic("mount_refdrain: dangling vnode"); 

	mp->mnt_lflag &= ~MNT_LDRAIN;

	return(0);
}