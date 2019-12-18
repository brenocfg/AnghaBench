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
 int /*<<< orphan*/  CYC_RESET ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  USE_CYCLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_output_reset () ; 

void m68k_op_reset(void)
{
	if(FLAG_S)
	{
		m68ki_output_reset();		   /* auto-disable (see m68kcpu.h) */
		USE_CYCLES(CYC_RESET);
		return;
	}
	m68ki_exception_privilege_violation();
}