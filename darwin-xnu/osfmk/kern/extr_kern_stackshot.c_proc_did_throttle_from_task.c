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
 int /*<<< orphan*/  proc_did_throttle (scalar_t__) ; 

__attribute__((used)) static uint64_t
proc_did_throttle_from_task(task_t task)
{
	uint64_t did_throttle = 0;

	if (task->bsd_info)
		did_throttle = proc_did_throttle(task->bsd_info);
	
	return did_throttle;
}