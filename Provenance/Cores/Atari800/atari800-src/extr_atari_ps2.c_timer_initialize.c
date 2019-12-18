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
 void* AddIntcHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableIntc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTC_TIM0 ; 
 int /*<<< orphan*/  INTC_TIM1 ; 
 scalar_t__ T0_COUNT ; 
 int T0_MODE ; 
 scalar_t__ T1_MODE ; 
 int /*<<< orphan*/  t0_interrupt_handler ; 
 void* t0_interrupt_id ; 
 int /*<<< orphan*/  t1_interrupt_handler ; 
 void* t1_interrupt_id ; 

__attribute__((used)) static void timer_initialize(void)
{
	T0_MODE = 0; // disable
	t0_interrupt_id = AddIntcHandler(INTC_TIM0, t0_interrupt_handler, 0);
	EnableIntc(INTC_TIM0);
	T0_COUNT = 0;
	T0_MODE = 0x002  // 576000 Hz clock
			+ 0x080  // start counting
			+ 0x200; // generate interrupt on overflow

	T1_MODE = 0; // disable
	t1_interrupt_id = AddIntcHandler(INTC_TIM1, t1_interrupt_handler, 0);
	EnableIntc(INTC_TIM1);
}