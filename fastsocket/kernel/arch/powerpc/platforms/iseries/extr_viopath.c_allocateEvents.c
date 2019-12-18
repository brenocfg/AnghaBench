#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct alloc_parms {int used_wait_atomic; int number; int /*<<< orphan*/  done; int /*<<< orphan*/  wait_atomic; } ;
typedef  int /*<<< orphan*/  HvLpIndex ;

/* Variables and functions */
 int /*<<< orphan*/  HvLpEvent_Type_VirtualIo ; 
 scalar_t__ SYSTEM_RUNNING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mf_allocate_lp_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,struct alloc_parms*) ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  viopath_donealloc ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allocateEvents(HvLpIndex remoteLp, int numEvents)
{
	struct alloc_parms parms;

	if (system_state != SYSTEM_RUNNING) {
		parms.used_wait_atomic = 1;
		atomic_set(&parms.wait_atomic, 1);
	} else {
		parms.used_wait_atomic = 0;
		init_completion(&parms.done);
	}
	mf_allocate_lp_events(remoteLp, HvLpEvent_Type_VirtualIo, 250,	/* It would be nice to put a real number here! */
			    numEvents, &viopath_donealloc, &parms);
	if (system_state != SYSTEM_RUNNING) {
		while (atomic_read(&parms.wait_atomic))
			mb();
	} else
		wait_for_completion(&parms.done);
	return parms.number;
}