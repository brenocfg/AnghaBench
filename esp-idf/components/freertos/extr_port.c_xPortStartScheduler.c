#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  _frxt_tick_timer_init () ; 
 int /*<<< orphan*/  _xt_coproc_init () ; 
 int /*<<< orphan*/  _xt_tick_divisor_init () ; 
 int /*<<< orphan*/  pdTRUE ; 
 int* port_xSchedulerRunning ; 
 size_t xPortGetCoreID () ; 

BaseType_t xPortStartScheduler( void )
{
	// Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored

	#if XCHAL_CP_NUM > 0
	/* Initialize co-processor management for tasks. Leave CPENABLE alone. */
	_xt_coproc_init();
	#endif

	/* Init the tick divisor value */
	_xt_tick_divisor_init();

	/* Setup the hardware to generate the tick. */
	_frxt_tick_timer_init();

	port_xSchedulerRunning[xPortGetCoreID()] = 1;

	// Cannot be directly called from C; never returns
	__asm__ volatile ("call0    _frxt_dispatch\n");

	/* Should not get here. */
	return pdTRUE;
}