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
 int /*<<< orphan*/  F0 ; 
 int /*<<< orphan*/  F1 ; 
 int /*<<< orphan*/  FC ; 
 int /*<<< orphan*/  PCCR ; 
 int /*<<< orphan*/  PCCR_C ; 
 int /*<<< orphan*/  PCCR_R ; 
 int SYSREG_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void avr32_perf_counter_reset(void)
{
	/* Reset all counter and disable/clear all interrupts */
	sysreg_write(PCCR, (SYSREG_BIT(PCCR_R)
				| SYSREG_BIT(PCCR_C)
				| SYSREG_BIT(FC)
				| SYSREG_BIT(F0)
				| SYSREG_BIT(F1)));
}