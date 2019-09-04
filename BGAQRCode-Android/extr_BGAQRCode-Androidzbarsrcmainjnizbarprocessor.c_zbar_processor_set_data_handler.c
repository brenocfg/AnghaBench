#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void const* userdata; int /*<<< orphan*/ * handler; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  int /*<<< orphan*/  zbar_image_data_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 

zbar_image_data_handler_t*
zbar_processor_set_data_handler (zbar_processor_t *proc,
                                 zbar_image_data_handler_t *handler,
                                 const void *userdata)
{
    zbar_image_data_handler_t *result = NULL;
    proc_enter(proc);

    result = proc->handler;
    proc->handler = handler;
    proc->userdata = userdata;

    proc_leave(proc);
    return(result);
}