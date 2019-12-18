#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mth_counts; } ;
struct TYPE_6__ {TYPE_1__ t_monotonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t MT_CORE_INSTRS ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_core_supported ; 
 int /*<<< orphan*/  mt_update_thread (TYPE_2__*) ; 

uint64_t
mt_cur_thread_instrs(void)
{
#ifdef MT_CORE_INSTRS
	thread_t curthread = current_thread();
	boolean_t intrs_en;
	uint64_t count;

	if (!mt_core_supported) {
		return 0;
	}

	intrs_en = ml_set_interrupts_enabled(FALSE);
	(void)mt_update_thread(curthread);
	count = curthread->t_monotonic.mth_counts[MT_CORE_INSTRS];
	ml_set_interrupts_enabled(intrs_en);

	return count;
#else /* defined(MT_CORE_INSTRS) */
	return 0;
#endif /* !defined(MT_CORE_INSTRS) */
}