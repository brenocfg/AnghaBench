#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sas_task {TYPE_1__* slow_task; int /*<<< orphan*/  task_state_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_TASK_STATE_ABORTED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pm8001_tmf_timedout(unsigned long data)
{
	struct sas_task *task = (struct sas_task *)data;

	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	complete(&task->slow_task->completion);
}