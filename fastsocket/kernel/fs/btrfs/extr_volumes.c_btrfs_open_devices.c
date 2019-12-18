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
struct btrfs_fs_devices {scalar_t__ opened; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int __btrfs_open_devices (struct btrfs_fs_devices*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_mutex ; 

int btrfs_open_devices(struct btrfs_fs_devices *fs_devices,
		       fmode_t flags, void *holder)
{
	int ret;

	mutex_lock(&uuid_mutex);
	if (fs_devices->opened) {
		fs_devices->opened++;
		ret = 0;
	} else {
		ret = __btrfs_open_devices(fs_devices, flags, holder);
	}
	mutex_unlock(&uuid_mutex);
	return ret;
}