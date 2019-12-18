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
struct path {int dummy; } ;
struct TYPE_2__ {int (* sb_check_sb ) (struct vfsmount*,struct path*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct vfsmount*,struct path*) ; 

int security_sb_check_sb(struct vfsmount *mnt, struct path *path)
{
	return security_ops->sb_check_sb(mnt, path);
}