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
typedef  TYPE_7__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_12__ {int /*<<< orphan*/  fpcr; } ;
struct TYPE_11__ {int /*<<< orphan*/  fpcr; } ;
struct TYPE_10__ {scalar_t__ flavor; } ;
struct TYPE_15__ {TYPE_3__ ns_32; TYPE_2__ ns_64; TYPE_1__ nsh; int /*<<< orphan*/  uns; } ;
struct TYPE_14__ {int /*<<< orphan*/  uss; } ;
struct TYPE_17__ {TYPE_6__ ns; TYPE_5__ ss; } ;
typedef  TYPE_8__ arm_context_t ;
struct TYPE_13__ {int /*<<< orphan*/ * DebugData; TYPE_8__* contextData; } ;
struct TYPE_16__ {TYPE_4__ machine; } ;

/* Variables and functions */
 scalar_t__ ARM_NEON_SAVED_STATE64 ; 
 int /*<<< orphan*/  FPCR_DEFAULT ; 
 int /*<<< orphan*/  FPCR_DEFAULT_32 ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

kern_return_t
machine_thread_state_initialize(
				thread_t thread)
{
	arm_context_t *context = thread->machine.contextData;

	/* 
	 * Should always be set up later. For a kernel thread, we don't care
	 * about this state. For a user thread, we'll set the state up in 
	 * setup_wqthread, bsdthread_create, load_main(), or load_unixthread().
	 */

	if (context != NULL) {
		bzero(&context->ss.uss, sizeof(context->ss.uss));
		bzero(&context->ns.uns, sizeof(context->ns.uns));

		if (context->ns.nsh.flavor == ARM_NEON_SAVED_STATE64) {
			context->ns.ns_64.fpcr = FPCR_DEFAULT;
		} else {
			context->ns.ns_32.fpcr = FPCR_DEFAULT_32;
		}
	}

	thread->machine.DebugData = NULL;


	return KERN_SUCCESS;
}