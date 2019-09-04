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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* exitHalt ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  cpu_to_lcpu (int) ; 
 TYPE_1__* pmDispatch ; 
 scalar_t__ pmInitDone ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

kern_return_t
pmCPUExitHalt(int cpu)
{
    kern_return_t	rc	= KERN_INVALID_ARGUMENT;

    if (pmInitDone
	&& pmDispatch != NULL
	&& pmDispatch->exitHalt != NULL)
	rc = pmDispatch->exitHalt(cpu_to_lcpu(cpu));

    return(rc);
}