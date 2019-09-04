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
struct _disk_conditioner_info_t {int /*<<< orphan*/  dcinfo; } ;
typedef  TYPE_1__* mount_t ;
typedef  int /*<<< orphan*/  disk_conditioner_info ;
struct TYPE_3__ {struct _disk_conditioner_info_t* mnt_disk_conditioner_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
disk_conditioner_get_info(mount_t mp, disk_conditioner_info *uinfo)
{
	struct _disk_conditioner_info_t *info;

	if (!mp) {
		return EINVAL;
	}

	info = mp->mnt_disk_conditioner_info;

	if (info) {
		memcpy(uinfo, &(info->dcinfo), sizeof(disk_conditioner_info));
	}

	return 0;
}