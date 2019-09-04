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
struct TYPE_5__ {unsigned long force_input; unsigned long force_output; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 

int zbar_processor_force_format (zbar_processor_t *proc,
                                 unsigned long input,
                                 unsigned long output)
{
    proc_enter(proc);
    proc->force_input = input;
    proc->force_output = output;
    proc_leave(proc);
    return(0);
}