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
typedef  TYPE_2__* thread_t ;
struct arm_saved_state {int /*<<< orphan*/  cpsr; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/ * DebugData; int /*<<< orphan*/  kVFPdata; int /*<<< orphan*/  uVFPdata; int /*<<< orphan*/  PcbData; } ;
struct TYPE_5__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PSR_USERDFLT ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  vfp_state_initialize (int /*<<< orphan*/ *) ; 

kern_return_t
machine_thread_state_initialize(
				thread_t thread)
{
	struct arm_saved_state *savestate;

	savestate = (struct arm_saved_state *) & thread->machine.PcbData;
	bzero((char *) savestate, sizeof(struct arm_saved_state));
	savestate->cpsr = PSR_USERDFLT;

#if __ARM_VFP__
	vfp_state_initialize(&thread->machine.uVFPdata);
	vfp_state_initialize(&thread->machine.kVFPdata);
#endif

	thread->machine.DebugData = NULL;

	return KERN_SUCCESS;
}