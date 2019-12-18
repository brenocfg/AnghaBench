#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  configfs_fs_type ; 
 int /*<<< orphan*/  configfs_mnt_count ; 
 int /*<<< orphan*/  configfs_mount ; 
 int simple_pin_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int configfs_pin_fs(void)
{
	return simple_pin_fs(&configfs_fs_type, &configfs_mount,
			     &configfs_mnt_count);
}