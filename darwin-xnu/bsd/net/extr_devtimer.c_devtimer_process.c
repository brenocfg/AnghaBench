#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* devtimer_timeout_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* devtimer_ref ;
typedef  int /*<<< orphan*/  (* devtimer_process_func ) (TYPE_1__*,int /*<<< orphan*/ ) ;
struct TYPE_6__ {int dt_generation; int /*<<< orphan*/  dt_arg2; int /*<<< orphan*/  dt_arg1; int /*<<< orphan*/  dt_arg0; int /*<<< orphan*/  (* dt_timeout_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dt_process_func ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  devtimer_process_func_event_lock ; 
 int /*<<< orphan*/  devtimer_process_func_event_unlock ; 
 int /*<<< orphan*/  devtimer_release (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devtimer_process(void * param0, void * param1)
{
    int				generation = *(int*)param1;
    devtimer_process_func 	process_func;
    devtimer_timeout_func 	timeout_func;
    devtimer_ref		timer = (devtimer_ref)param0;

    process_func = timer->dt_process_func;
    if (process_func != NULL) {
	(*process_func)(timer, devtimer_process_func_event_lock);
    }
    timeout_func = timer->dt_timeout_func;
    if (timeout_func != NULL) {
	timer->dt_timeout_func = NULL;
	if (timer->dt_generation == generation) {
	    (*timeout_func)(timer->dt_arg0, timer->dt_arg1, timer->dt_arg2);
	}
    }
    devtimer_release(timer);
    if (process_func != NULL) {
	(*process_func)(timer, devtimer_process_func_event_unlock);
    }
    return;
}