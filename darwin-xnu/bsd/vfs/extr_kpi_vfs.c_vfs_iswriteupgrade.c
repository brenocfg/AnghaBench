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
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {int mnt_flag; int mnt_kern_flag; } ;

/* Variables and functions */
 int MNTK_WANTRDWR ; 
 int MNT_RDONLY ; 

int 
vfs_iswriteupgrade(mount_t mp) /* ronly &&  MNTK_WANTRDWR */
{
	return ((mp->mnt_flag & MNT_RDONLY) && (mp->mnt_kern_flag & MNTK_WANTRDWR));
}