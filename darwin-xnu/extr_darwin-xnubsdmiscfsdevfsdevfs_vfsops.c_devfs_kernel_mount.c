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
typedef  int /*<<< orphan*/  vfs_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_MOUNT_NOAUTH ; 
 int /*<<< orphan*/  MNT_DONTBROWSE ; 
 int /*<<< orphan*/  NULLVP ; 
 int kernel_mount (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 

int
devfs_kernel_mount(char * mntname)
{
	int error;
	vfs_context_t ctx = vfs_context_kernel();
	char fsname[] = "devfs";

	error = kernel_mount(fsname, NULLVP, NULLVP, mntname, NULL, 0, MNT_DONTBROWSE, KERNEL_MOUNT_NOAUTH, ctx);
	if (error) {
		printf("devfs_kernel_mount: kernel_mount failed: %d\n", error);
		return (error);
	}

	return (0);
}