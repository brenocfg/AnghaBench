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
 int /*<<< orphan*/  EA_AL_16 () ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_get_ccr () ; 
 int /*<<< orphan*/  m68ki_write_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void m68k_op_move_16_frc_al(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		m68ki_write_16(EA_AL_16(), m68ki_get_ccr());
		return;
	}
	m68ki_exception_illegal();
}