#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct memcg_batch_info {TYPE_1__* memcg; scalar_t__ memsw_bytes; scalar_t__ bytes; scalar_t__ do_batch; } ;
struct TYPE_4__ {struct memcg_batch_info memcg_batch; } ;
struct TYPE_3__ {int /*<<< orphan*/  memsw; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  memcg_oom_recover (TYPE_1__*) ; 
 int /*<<< orphan*/  res_counter_uncharge (int /*<<< orphan*/ *,scalar_t__) ; 

void mem_cgroup_uncharge_end(void)
{
	struct memcg_batch_info *batch = &current->memcg_batch;

	if (!batch->do_batch)
		return;

	batch->do_batch--;
	if (batch->do_batch) /* If stacked, do nothing. */
		return;

	if (!batch->memcg)
		return;
	/*
	 * This "batch->memcg" is valid without any css_get/put etc...
	 * bacause we hide charges behind us.
	 */
	if (batch->bytes)
		res_counter_uncharge(&batch->memcg->res, batch->bytes);
	if (batch->memsw_bytes)
		res_counter_uncharge(&batch->memcg->memsw, batch->memsw_bytes);
	memcg_oom_recover(batch->memcg);
	/* forget this pointer (for sanity check) */
	batch->memcg = NULL;
}