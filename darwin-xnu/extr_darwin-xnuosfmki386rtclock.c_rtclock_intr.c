#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_6__ {int cs; int /*<<< orphan*/  rip; } ;
struct TYPE_7__ {TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {int cs; int /*<<< orphan*/  eip; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_preemption_level () ; 
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 TYPE_3__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_intr (scalar_t__,int /*<<< orphan*/ ) ; 

void
rtclock_intr(
	x86_saved_state_t	*tregs)
{
        uint64_t	rip;
	boolean_t	user_mode = FALSE;

	assert(get_preemption_level() > 0);
	assert(!ml_get_interrupts_enabled());

	if (is_saved_state64(tregs) == TRUE) {
	        x86_saved_state64_t	*regs;
		  
		regs = saved_state64(tregs);

		if (regs->isf.cs & 0x03)
			user_mode = TRUE;
		rip = regs->isf.rip;
	} else {
	        x86_saved_state32_t	*regs;

		regs = saved_state32(tregs);

		if (regs->cs & 0x03)
		        user_mode = TRUE;
		rip = regs->eip;
	}

	/* call the generic etimer */
	timer_intr(user_mode, rip);
}