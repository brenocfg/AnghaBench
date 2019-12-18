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
typedef  scalar_t__ u64 ;
struct debug_store {scalar_t__ bts_absolute_maximum; scalar_t__ bts_interrupt_threshold; scalar_t__ bts_buffer_base; scalar_t__ bts_index; } ;
struct TYPE_4__ {struct debug_store* ds; } ;
struct TYPE_3__ {int /*<<< orphan*/  bts; } ;

/* Variables and functions */
 int BTS_BUFFER_SIZE ; 
 int BTS_RECORD_SIZE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int cpu_to_node (int) ; 
 void* kmalloc_node (int,int,int) ; 
 TYPE_2__ per_cpu (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int alloc_bts_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	int node = cpu_to_node(cpu);
	int max, thresh;
	void *buffer;

	if (!x86_pmu.bts)
		return 0;

	buffer = kmalloc_node(BTS_BUFFER_SIZE, GFP_KERNEL | __GFP_ZERO, node);
	if (unlikely(!buffer))
		return -ENOMEM;

	max = BTS_BUFFER_SIZE / BTS_RECORD_SIZE;
	thresh = max / 16;

	ds->bts_buffer_base = (u64)(unsigned long)buffer;
	ds->bts_index = ds->bts_buffer_base;
	ds->bts_absolute_maximum = ds->bts_buffer_base +
		max * BTS_RECORD_SIZE;
	ds->bts_interrupt_threshold = ds->bts_absolute_maximum -
		thresh * BTS_RECORD_SIZE;

	return 0;
}