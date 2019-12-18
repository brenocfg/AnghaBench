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
typedef  int /*<<< orphan*/  retro_task_condition_fn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 TYPE_1__* impl_current ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

void task_queue_wait(retro_task_condition_fn_t cond, void* data)
{
   impl_current->wait(cond, data);
}