#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_4__ {scalar_t__* mth_counts; } ;
struct TYPE_5__ {TYPE_1__ t_monotonic; } ;

/* Variables and functions */
 size_t MT_CORE_CYCLES ; 
 size_t MT_CORE_INSTRS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_core_supported ; 

void
mt_stackshot_thread(thread_t thread, uint64_t *instrs, uint64_t *cycles)
{
	assert(mt_core_supported);

#ifdef MT_CORE_INSTRS
	*instrs = thread->t_monotonic.mth_counts[MT_CORE_INSTRS];
#else /* defined(MT_CORE_INSTRS) */
	*instrs = 0;
#endif /* !defined(MT_CORE_INSTRS) */

	*cycles = thread->t_monotonic.mth_counts[MT_CORE_CYCLES];
}