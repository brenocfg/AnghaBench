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
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_010_PLUS (int /*<<< orphan*/ ) ; 
 int DY ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int m68ki_get_ccr () ; 

void m68k_op_move_16_frc_d(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		DY = MASK_OUT_BELOW_16(DY) | m68ki_get_ccr();
		return;
	}
	m68ki_exception_illegal();
}