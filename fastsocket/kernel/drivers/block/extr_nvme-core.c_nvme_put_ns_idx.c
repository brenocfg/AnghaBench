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
 int /*<<< orphan*/  dev_list_lock ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvme_index_ida ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_put_ns_idx(int index)
{
	spin_lock(&dev_list_lock);
	ida_remove(&nvme_index_ida, index);
	spin_unlock(&dev_list_lock);
}