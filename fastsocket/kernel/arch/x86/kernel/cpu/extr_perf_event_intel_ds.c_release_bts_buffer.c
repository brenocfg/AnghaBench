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
struct debug_store {scalar_t__ bts_buffer_base; } ;
struct TYPE_4__ {struct debug_store* ds; } ;
struct TYPE_3__ {int /*<<< orphan*/  bts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  kfree (void*) ; 
 TYPE_2__ per_cpu (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static void release_bts_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds || !x86_pmu.bts)
		return;

	kfree((void *)(unsigned long)ds->bts_buffer_base);
	ds->bts_buffer_base = 0;
}