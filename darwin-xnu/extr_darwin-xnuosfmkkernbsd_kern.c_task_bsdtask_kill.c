#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 void* get_bsdtask_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psignal (void*,int /*<<< orphan*/ ) ; 

void task_bsdtask_kill(task_t t)
{
	void * bsd_info = get_bsdtask_info(t);
	if (bsd_info != NULL) {
		psignal(bsd_info, SIGKILL);
	}
}