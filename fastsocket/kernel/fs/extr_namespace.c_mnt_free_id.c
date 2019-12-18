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
struct vfsmount {int mnt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mnt_id_ida ; 
 int mnt_id_start ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static void mnt_free_id(struct vfsmount *mnt)
{
	int id = mnt->mnt_id;
	spin_lock(&vfsmount_lock);
	ida_remove(&mnt_id_ida, id);
	if (mnt_id_start > id)
		mnt_id_start = id;
	spin_unlock(&vfsmount_lock);
}