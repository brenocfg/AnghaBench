#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int done; TYPE_2__* super; int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* func ) (TYPE_1__* const,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ccv_nnc_stream_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  caller; int /*<<< orphan*/  callee; } ;
typedef  TYPE_2__ ccv_nnc_stream_scheduler_t ;
struct TYPE_7__ {scalar_t__ ptr; int /*<<< orphan*/  part; } ;
typedef  TYPE_3__ ccv_nnc_ptr_splitter_u ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_stream_task_entry_point(uint32_t part0, uint32_t part1)
{
	const ccv_nnc_ptr_splitter_u p = {
		.part = {
			part0, part1
		}
	};
	ccv_nnc_stream_task_t* const task = (ccv_nnc_stream_task_t*)p.ptr;
	task->func(task, task->userdata);
	ccv_nnc_stream_scheduler_t* const scheduler = task->super;
	task->done = 1;
	swapcontext(&scheduler->callee, &scheduler->caller);
}