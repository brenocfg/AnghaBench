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
struct TYPE_3__ {int do_batch; scalar_t__ memsw_bytes; scalar_t__ bytes; int /*<<< orphan*/ * memcg; } ;
struct TYPE_4__ {TYPE_1__ memcg_batch; } ;

/* Variables and functions */
 TYPE_2__* current ; 

void mem_cgroup_uncharge_start(void)
{
	current->memcg_batch.do_batch++;
	/* We can do nest. */
	if (current->memcg_batch.do_batch == 1) {
		current->memcg_batch.memcg = NULL;
		current->memcg_batch.bytes = 0;
		current->memcg_batch.memsw_bytes = 0;
	}
}