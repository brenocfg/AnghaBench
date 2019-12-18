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
struct exofs_i_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  i_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  is_bad_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_2bcreated (struct exofs_i_info*) ; 
 int /*<<< orphan*/  obj_created (struct exofs_i_info*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __exofs_wait_obj_created(struct exofs_i_info *oi)
{
	if (!obj_created(oi)) {
		BUG_ON(!obj_2bcreated(oi));
		wait_event(oi->i_wq, obj_created(oi));
	}
	return unlikely(is_bad_inode(&oi->vfs_inode)) ? -EIO : 0;
}