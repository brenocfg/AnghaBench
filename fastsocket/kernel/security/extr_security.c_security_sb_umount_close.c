#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sb_umount_close ) (struct vfsmount*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct vfsmount*) ; 

void security_sb_umount_close(struct vfsmount *mnt)
{
	security_ops->sb_umount_close(mnt);
}