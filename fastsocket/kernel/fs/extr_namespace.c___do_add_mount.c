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
struct vfsmount {int dummy; } ;
struct path {int dummy; } ;

/* Variables and functions */
 int do_add_mount_unlocked (struct vfsmount*,struct path*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __do_add_mount(struct vfsmount *newmnt, struct path *path, int mnt_flags)
{
	int err;

	down_write(&namespace_sem);
	err = do_add_mount_unlocked(newmnt, path, mnt_flags);
	up_write(&namespace_sem);
	return err;
}