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
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ uu_proc_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_uthread () ; 

__attribute__((used)) static boolean_t
uthread_needs_to_wait_in_proc_refwait(void) {
	uthread_t uth = current_uthread();

	/*
	 * Allow threads holding no proc refs to wait
	 * in proc_refwait, allowing threads holding
	 * proc refs to wait in proc_refwait causes
	 * deadlocks and makes proc_find non-reentrant.
	 */
	if (uth->uu_proc_refcount == 0)
		return TRUE;

	return FALSE;
}