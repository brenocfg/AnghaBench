#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_5__ {void* bsd_info; } ;
struct TYPE_4__ {TYPE_3__* task; } ;

/* Variables and functions */
 TYPE_3__* TASK_NULL ; 

void *get_bsdthreadtask_info(thread_t th)
{
	return(th->task != TASK_NULL ? th->task->bsd_info : NULL);
}