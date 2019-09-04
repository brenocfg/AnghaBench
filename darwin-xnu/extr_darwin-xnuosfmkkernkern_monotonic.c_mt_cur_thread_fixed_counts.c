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
typedef  scalar_t__ uint64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {scalar_t__* mth_counts; } ;
struct TYPE_6__ {TYPE_1__ t_monotonic; } ;

/* Variables and functions */
 int FALSE ; 
 int MT_CORE_NFIXED ; 
 TYPE_2__* current_thread () ; 
 int ml_set_interrupts_enabled (int) ; 
 int /*<<< orphan*/  mt_core_supported ; 
 int /*<<< orphan*/  mt_update_thread (TYPE_2__*) ; 

void
mt_cur_thread_fixed_counts(uint64_t *counts)
{
	if (!mt_core_supported) {
		for (int i = 0; i < MT_CORE_NFIXED; i++) {
			counts[i] = 0;
		}
		return;
	}

	thread_t curthread = current_thread();
	int intrs_en = ml_set_interrupts_enabled(FALSE);
	(void)mt_update_thread(curthread);
	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		counts[i] = curthread->t_monotonic.mth_counts[i];
	}
	ml_set_interrupts_enabled(intrs_en);
}