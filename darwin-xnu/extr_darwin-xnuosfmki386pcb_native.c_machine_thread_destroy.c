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
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* pcb_t ;
struct TYPE_3__ {scalar_t__ ifps; scalar_t__ iss; int /*<<< orphan*/ * ids; } ;

/* Variables and functions */
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ids_zone ; 
 int /*<<< orphan*/  iss_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
machine_thread_destroy(
	thread_t		thread)
{
	pcb_t	pcb = THREAD_TO_PCB(thread);

#if HYPERVISOR
	if (thread->hv_thread_target) {
		hv_callbacks.thread_destroy(thread->hv_thread_target);
		thread->hv_thread_target = NULL;
	}
#endif

	if (pcb->ifps != 0)
		fpu_free(thread, pcb->ifps);
	if (pcb->iss != 0) {
		zfree(iss_zone, pcb->iss);
		pcb->iss = 0;
	}
	if (pcb->ids) {
		zfree(ids_zone, pcb->ids);
		pcb->ids = NULL;
	}
}