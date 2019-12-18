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
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int REG_IR ; 
 int /*<<< orphan*/  m68ki_bkpt_ack (int) ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 

void m68k_op_bkpt(void)
{
	if(CPU_TYPE_IS_010_PLUS(CPU_TYPE))
	{
		m68ki_bkpt_ack(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE) ? REG_IR & 7 : 0);	/* auto-disable (see m68kcpu.h) */
	}
	m68ki_exception_illegal();
}