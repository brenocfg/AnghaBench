#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ prof_cyclic; scalar_t__ prof_kind; } ;
typedef  TYPE_1__ profile_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
typedef  int /*<<< orphan*/  cyclic_id_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ CYCLIC_NONE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ PROF_TICK ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  cyclic_remove_omni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyclic_timer_remove (scalar_t__) ; 

__attribute__((used)) static void
profile_disable(void *arg, dtrace_id_t id, void *parg)
{
	profile_probe_t *prof = parg;

	ASSERT(prof->prof_cyclic != CYCLIC_NONE);
	ASSERT(MUTEX_HELD(&cpu_lock));

#pragma unused(arg,id)
	if (prof->prof_kind == PROF_TICK) {
		cyclic_timer_remove(prof->prof_cyclic);
	} else {
		cyclic_remove_omni((cyclic_id_list_t)prof->prof_cyclic); /* cast puns cyclic_id_list_t with cyclic_id_t */
	}
	prof->prof_cyclic = CYCLIC_NONE;
}