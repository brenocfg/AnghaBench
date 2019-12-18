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
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {int /*<<< orphan*/  audit_token; } ;

/* Variables and functions */
 int get_audit_token_pid (int /*<<< orphan*/ *) ; 

int task_pid(task_t task)
{
	if (task)
		return get_audit_token_pid(&task->audit_token);
	return -1;
}