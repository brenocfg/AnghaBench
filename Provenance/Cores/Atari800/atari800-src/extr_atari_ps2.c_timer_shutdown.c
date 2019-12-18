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

/* Variables and functions */
 int /*<<< orphan*/  DisableIntc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTC_TIM0 ; 
 int /*<<< orphan*/  INTC_TIM1 ; 
 int /*<<< orphan*/  RemoveIntcHandler (int /*<<< orphan*/ ,int) ; 
 scalar_t__ T0_MODE ; 
 scalar_t__ T1_MODE ; 
 int t0_interrupt_id ; 
 int t1_interrupt_id ; 

__attribute__((used)) static void timer_shutdown(void)
{
	T0_MODE = 0;
	if (t0_interrupt_id >= 0) {
		DisableIntc(INTC_TIM0);
		RemoveIntcHandler(INTC_TIM0, t0_interrupt_id);
		t0_interrupt_id = -1;
	}
	T1_MODE = 0;
	if (t1_interrupt_id >= 0) {
		DisableIntc(INTC_TIM1);
		RemoveIntcHandler(INTC_TIM1, t1_interrupt_id);
		t1_interrupt_id = -1;
	}
}