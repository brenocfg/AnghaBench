#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* pcb_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* thread_destroy ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {scalar_t__ ifps; scalar_t__ iss; int /*<<< orphan*/ * ids; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hv_thread_target; } ;

/* Variables and functions */
 TYPE_2__* THREAD_TO_PCB (TYPE_1__*) ; 
 int /*<<< orphan*/  fpu_free (TYPE_1__*,scalar_t__) ; 
 TYPE_4__ hv_callbacks ; 
 int /*<<< orphan*/  ids_zone ; 
 int /*<<< orphan*/  iss_zone ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
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