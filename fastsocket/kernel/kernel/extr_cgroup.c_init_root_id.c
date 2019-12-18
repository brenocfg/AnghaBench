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
struct cgroupfs_root {scalar_t__ hierarchy_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hierarchy_id_lock ; 
 int /*<<< orphan*/  hierarchy_ida ; 
 int ida_get_new (int /*<<< orphan*/ *,scalar_t__*) ; 
 int ida_get_new_above (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ next_hierarchy_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_root_id(struct cgroupfs_root *root)
{
	int ret = 0;

	do {
		if (!ida_pre_get(&hierarchy_ida, GFP_KERNEL))
			return false;
		spin_lock(&hierarchy_id_lock);
		/* Try to allocate the next unused ID */
		ret = ida_get_new_above(&hierarchy_ida, next_hierarchy_id,
					&root->hierarchy_id);
		if (ret == -ENOSPC)
			/* Try again starting from 0 */
			ret = ida_get_new(&hierarchy_ida, &root->hierarchy_id);
		if (!ret) {
			next_hierarchy_id = root->hierarchy_id + 1;
		} else if (ret != -EAGAIN) {
			/* Can only get here if the 31-bit IDR is full ... */
			BUG_ON(ret);
		}
		spin_unlock(&hierarchy_id_lock);
	} while (ret);
	return true;
}