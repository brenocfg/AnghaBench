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
struct tasklet_struct {unsigned long data; } ;
struct flow_flush_info {TYPE_1__* cache; } ;
struct TYPE_4__ {struct tasklet_struct flush_tasklet; } ;
struct TYPE_3__ {int /*<<< orphan*/  percpu; } ;

/* Variables and functions */
 TYPE_2__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tasklet_schedule (struct tasklet_struct*) ; 

__attribute__((used)) static void flow_cache_flush_per_cpu(void *data)
{
	struct flow_flush_info *info = data;
	int cpu;
	struct tasklet_struct *tasklet;

	cpu = smp_processor_id();
	tasklet = &per_cpu_ptr(info->cache->percpu, cpu)->flush_tasklet;
	tasklet->data = (unsigned long)info;
	tasklet_schedule(tasklet);
}