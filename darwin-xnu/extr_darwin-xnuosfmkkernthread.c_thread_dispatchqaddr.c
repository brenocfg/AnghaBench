#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_8__ {scalar_t__ bsd_info; } ;
struct TYPE_6__ {scalar_t__ cthread_self; } ;
struct TYPE_7__ {scalar_t__ inspection; TYPE_4__* task; TYPE_1__ machine; } ;

/* Variables and functions */
 TYPE_2__* THREAD_NULL ; 
 scalar_t__ TRUE ; 
 scalar_t__ get_dispatchqueue_offset_from_proc (scalar_t__) ; 
 scalar_t__ get_task_dispatchqueue_offset (TYPE_4__*) ; 

uint64_t
thread_dispatchqaddr(
	thread_t		thread)
{
	uint64_t	dispatchqueue_addr;
	uint64_t	thread_handle;

	if (thread == THREAD_NULL)
		return 0;

	thread_handle = thread->machine.cthread_self;
	if (thread_handle == 0)
		return 0;
	
	if (thread->inspection == TRUE)
		dispatchqueue_addr = thread_handle + get_task_dispatchqueue_offset(thread->task);
	else if (thread->task->bsd_info)
		dispatchqueue_addr = thread_handle + get_dispatchqueue_offset_from_proc(thread->task->bsd_info);
	else
		dispatchqueue_addr = 0;

	return dispatchqueue_addr;
}