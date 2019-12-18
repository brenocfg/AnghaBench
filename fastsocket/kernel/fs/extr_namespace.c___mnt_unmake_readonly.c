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
struct vfsmount {int /*<<< orphan*/  mnt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_READONLY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static void __mnt_unmake_readonly(struct vfsmount *mnt)
{
	spin_lock(&vfsmount_lock);
	mnt->mnt_flags &= ~MNT_READONLY;
	spin_unlock(&vfsmount_lock);
}