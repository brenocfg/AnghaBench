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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EA_AY_PI_16 () ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_get_sr () ; 
 int /*<<< orphan*/  m68ki_write_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void m68k_op_move_16_frs_pi(void)
{
	if(CPU_TYPE_IS_000(CPU_TYPE) || FLAG_S)	/* NS990408 */
	{
		uint ea = EA_AY_PI_16();
		m68ki_write_16(ea, m68ki_get_sr());
		return;
	}
	m68ki_exception_privilege_violation();
}