#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  kperf_flags; int /*<<< orphan*/  kpc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KPC_MAX_COUNTERS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  T_KPC_ALLOC ; 
 int /*<<< orphan*/  act_set_kperf (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ kpc_get_counter_count (scalar_t__) ; 
 int /*<<< orphan*/  kpc_off_cpu_update () ; 
 scalar_t__ kpc_thread_classes ; 
 scalar_t__ kpc_thread_classes_count ; 
 int /*<<< orphan*/  kpc_thread_lock ; 
 int /*<<< orphan*/  kpc_threads_counting ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
kpc_set_thread_counting(uint32_t classes)
{
	uint32_t count;

	lck_mtx_lock(&kpc_thread_lock);

	count = kpc_get_counter_count(classes);

	if( (classes == 0)
	    || (count == 0) )
	{
		/* shut down */
		kpc_threads_counting = FALSE;
	}
	else
	{
		/* stash the config */
		kpc_thread_classes = classes;

		/* work out the size */
		kpc_thread_classes_count = count;
		assert(kpc_thread_classes_count <= KPC_MAX_COUNTERS);

		/* enable switch */
		kpc_threads_counting = TRUE;

		/* and schedule an AST for this thread... */
		if( !current_thread()->kpc_buf )
		{
			current_thread()->kperf_flags |= T_KPC_ALLOC;
			act_set_kperf(current_thread());
		}
	}

    kpc_off_cpu_update();
	lck_mtx_unlock(&kpc_thread_lock);

	return 0;
}