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
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_list_lock ; 
 int ida_get_new (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_index_ida ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_get_ns_idx(void)
{
	int index, error;

	do {
		if (!ida_pre_get(&nvme_index_ida, GFP_KERNEL))
			return -1;

		spin_lock(&dev_list_lock);
		error = ida_get_new(&nvme_index_ida, &index);
		spin_unlock(&dev_list_lock);
	} while (error == -EAGAIN);

	if (error)
		index = -1;
	return index;
}