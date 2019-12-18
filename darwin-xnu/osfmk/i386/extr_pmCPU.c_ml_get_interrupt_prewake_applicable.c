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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pmInterruptPrewakeApplicable ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* pmDispatch ; 
 scalar_t__ pmInitDone ; 
 int /*<<< orphan*/  stub1 () ; 

boolean_t
ml_get_interrupt_prewake_applicable()
{
    boolean_t applicable = FALSE;

    if (pmInitDone 
	&& pmDispatch != NULL
	&& pmDispatch->pmInterruptPrewakeApplicable != NULL)
	applicable = pmDispatch->pmInterruptPrewakeApplicable();

    return applicable;
}