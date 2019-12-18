#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_8__ {scalar_t__** cpu_kpc_buf; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_9__ {int /*<<< orphan*/  kperf_flags; int /*<<< orphan*/  kpc_buf; } ;
struct TYPE_7__ {int /*<<< orphan*/ * kpc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  T_KPC_ALLOC ; 
 int /*<<< orphan*/  act_set_kperf (TYPE_4__*) ; 
 TYPE_2__* current_cpu_datap () ; 
 TYPE_4__* current_thread () ; 
 int /*<<< orphan*/  kpc_get_cpu_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  kpc_thread_classes ; 
 size_t kpc_thread_classes_count ; 

__attribute__((used)) static void
kpc_update_thread_counters( thread_t thread )
{
	uint32_t i;
	uint64_t *tmp = NULL;
	cpu_data_t *cpu = NULL;

	cpu = current_cpu_datap();

	/* 1. stash current PMCs into latest CPU block */
	kpc_get_cpu_counters( FALSE, kpc_thread_classes, 
	                      NULL, cpu->cpu_kpc_buf[1] );

	/* 2. apply delta to old thread */
	if( thread->kpc_buf )
		for( i = 0; i < kpc_thread_classes_count; i++ )
			thread->kpc_buf[i] += cpu->cpu_kpc_buf[1][i] - cpu->cpu_kpc_buf[0][i];

	/* schedule any necessary allocations */
	if( !current_thread()->kpc_buf )
	{
		current_thread()->kperf_flags |= T_KPC_ALLOC;
		act_set_kperf(current_thread());
	}

	/* 3. switch the PMC block pointers */
	tmp = cpu->cpu_kpc_buf[1];
	cpu->cpu_kpc_buf[1] = cpu->cpu_kpc_buf[0];
	cpu->cpu_kpc_buf[0] = tmp;
}