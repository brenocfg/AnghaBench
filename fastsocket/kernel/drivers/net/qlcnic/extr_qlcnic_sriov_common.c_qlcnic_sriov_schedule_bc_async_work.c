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
typedef  int /*<<< orphan*/  work_func_t ;
struct qlcnic_back_channel {int /*<<< orphan*/  bc_async_wq; } ;
struct qlcnic_async_work_list {int /*<<< orphan*/  work; void* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qlcnic_async_work_list* qlcnic_sriov_get_free_node_async_work (struct qlcnic_back_channel*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_schedule_bc_async_work(struct qlcnic_back_channel *bc,
						work_func_t func, void *data)
{
	struct qlcnic_async_work_list *entry = NULL;

	entry = qlcnic_sriov_get_free_node_async_work(bc);
	if (!entry)
		return;

	entry->ptr = data;
	INIT_WORK(&entry->work, func);
	queue_work(bc->bc_async_wq, &entry->work);
}