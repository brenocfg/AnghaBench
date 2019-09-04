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
struct TYPE_5__ {TYPE_1__* mnt_vtable; } ;
struct TYPE_4__ {int vfc_vfsflags; } ;

/* Variables and functions */
 int VFC_VFS64BITREADY ; 

int
vfs_64bitready(mount_t mp)
{
	if ((mp->mnt_vtable->vfc_vfsflags & VFC_VFS64BITREADY))
		return(1);
	else
		return(0);
}