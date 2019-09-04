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
struct TYPE_5__ {int /*<<< orphan*/  visible; scalar_t__ window; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 

int zbar_processor_is_visible (zbar_processor_t *proc)
{
    proc_enter(proc);
    int visible = proc->window && proc->visible;
    proc_leave(proc);
    return(visible);
}