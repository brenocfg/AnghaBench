#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lcpu; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* exitIdle ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* pmDispatch ; 
 scalar_t__ pmInitDone ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

boolean_t
pmCPUExitIdle(cpu_data_t *cpu)
{
    boolean_t		do_ipi;

    if (pmInitDone
	&& pmDispatch != NULL
	&& pmDispatch->exitIdle != NULL)
	do_ipi = (*pmDispatch->exitIdle)(&cpu->lcpu);
    else
	do_ipi = TRUE;

    return(do_ipi);
}