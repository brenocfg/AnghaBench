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
struct TYPE_3__ {int mnt_lflag; } ;

/* Variables and functions */
 int MNT_LUNMOUNT ; 

int
vfs_isunmount(mount_t mp)
{
	if ((mp->mnt_lflag & MNT_LUNMOUNT)) {
		return 1;
	} else {
		return 0;
	}
}