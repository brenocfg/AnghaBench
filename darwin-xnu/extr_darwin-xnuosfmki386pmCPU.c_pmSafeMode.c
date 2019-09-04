#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_1__ x86_lcpu_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* pmCPUSafeMode ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 scalar_t__ LCPU_PAUSE ; 
 scalar_t__ LCPU_RUN ; 
 int PM_SAFE_FL_PAUSE ; 
 int PM_SAFE_FL_RESUME ; 
 int /*<<< orphan*/  cpu_pause () ; 
 TYPE_5__* pmDispatch ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 TYPE_1__* x86_lcpu () ; 

void
pmSafeMode(x86_lcpu_t *lcpu, uint32_t flags)
{
    if (pmDispatch != NULL
	&& pmDispatch->pmCPUSafeMode != NULL)
	pmDispatch->pmCPUSafeMode(lcpu, flags);
    else {
	/*
	 * Do something reasonable if the KEXT isn't present.
	 *
	 * We only look at the PAUSE and RESUME flags.  The other flag(s)
	 * will not make any sense without the KEXT, so just ignore them.
	 *
	 * We set the CPU's state to indicate that it's halted.  If this
	 * is the CPU we're currently running on, then spin until the
	 * state becomes non-halted.
	 */
	if (flags & PM_SAFE_FL_PAUSE) {
	    lcpu->state = LCPU_PAUSE;
	    if (lcpu == x86_lcpu()) {
		while (lcpu->state == LCPU_PAUSE)
		    cpu_pause();
	    }
	}
	
	/*
	 * Clear the halted flag for the specified CPU, that will
	 * get it out of it's spin loop.
	 */
	if (flags & PM_SAFE_FL_RESUME) {
	    lcpu->state = LCPU_RUN;
	}
    }
}