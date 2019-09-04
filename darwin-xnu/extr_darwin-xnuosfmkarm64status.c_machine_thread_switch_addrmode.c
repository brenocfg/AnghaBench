#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_8__* thread_t ;
struct TYPE_16__ {TYPE_6__* uNeon; TYPE_3__* upcb; } ;
struct TYPE_17__ {TYPE_7__ machine; int /*<<< orphan*/  task; } ;
struct TYPE_14__ {int /*<<< orphan*/  fpcr; } ;
struct TYPE_13__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_10__ {int /*<<< orphan*/  fpcr; } ;
struct TYPE_15__ {TYPE_5__ ns_32; int /*<<< orphan*/  uns; TYPE_4__ nsh; TYPE_1__ ns_64; } ;
struct TYPE_11__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_12__ {TYPE_2__ ash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE32 ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE64 ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE64_COUNT ; 
 int /*<<< orphan*/  ARM_SAVED_STATE32 ; 
 int /*<<< orphan*/  ARM_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  ARM_SAVED_STATE64 ; 
 int /*<<< orphan*/  ARM_SAVED_STATE64_COUNT ; 
 int /*<<< orphan*/  FPCR_DEFAULT ; 
 int /*<<< orphan*/  FPCR_DEFAULT_32 ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ task_has_64Bit_data (int /*<<< orphan*/ ) ; 

void
machine_thread_switch_addrmode(thread_t thread)
{
	if (task_has_64Bit_data(thread->task)) {
		thread->machine.upcb->ash.flavor = ARM_SAVED_STATE64;
		thread->machine.upcb->ash.count = ARM_SAVED_STATE64_COUNT;
		thread->machine.uNeon->nsh.flavor = ARM_NEON_SAVED_STATE64;
		thread->machine.uNeon->nsh.count = ARM_NEON_SAVED_STATE64_COUNT;

		/*
		 * Reinitialize the NEON state.
		 */
		bzero(&thread->machine.uNeon->uns, sizeof(thread->machine.uNeon->uns));
		thread->machine.uNeon->ns_64.fpcr = FPCR_DEFAULT;
	} else {
		thread->machine.upcb->ash.flavor = ARM_SAVED_STATE32;
		thread->machine.upcb->ash.count = ARM_SAVED_STATE32_COUNT;
		thread->machine.uNeon->nsh.flavor = ARM_NEON_SAVED_STATE32;
		thread->machine.uNeon->nsh.count = ARM_NEON_SAVED_STATE32_COUNT;

		/*
		 * Reinitialize the NEON state.
		 */
		bzero(&thread->machine.uNeon->uns, sizeof(thread->machine.uNeon->uns));
		thread->machine.uNeon->ns_32.fpcr = FPCR_DEFAULT_32;
	}
}