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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {scalar_t__ bsd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_dispatchqueue_serialno_offset_from_proc (scalar_t__) ; 

uint64_t
get_task_dispatchqueue_serialno_offset(task_t task)
{
	uint64_t dq_serialno_offset = 0;

	if (task->bsd_info) {
		dq_serialno_offset = get_dispatchqueue_serialno_offset_from_proc(task->bsd_info);
	}

	return dq_serialno_offset;
}