#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * th_work_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  thread_set_work_interval (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
work_interval_thread_terminate(thread_t thread)
{
	if (thread->th_work_interval != NULL)
		thread_set_work_interval(thread, NULL);
}