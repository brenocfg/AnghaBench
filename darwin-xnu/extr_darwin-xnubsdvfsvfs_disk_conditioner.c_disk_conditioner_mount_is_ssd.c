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
struct TYPE_4__ {int is_ssd; int /*<<< orphan*/  enabled; } ;
struct _disk_conditioner_info_t {TYPE_1__ dcinfo; } ;
typedef  TYPE_2__* mount_t ;
typedef  int boolean_t ;
struct TYPE_5__ {int mnt_kern_flag; struct _disk_conditioner_info_t* mnt_disk_conditioner_info; } ;

/* Variables and functions */
 int MNTK_SSD ; 

boolean_t
disk_conditioner_mount_is_ssd(mount_t mp)
{
	struct _disk_conditioner_info_t *internal_info = mp->mnt_disk_conditioner_info;

	if (!internal_info || !internal_info->dcinfo.enabled) {
		return !!(mp->mnt_kern_flag & MNTK_SSD);
	}

	return internal_info->dcinfo.is_ssd;
}