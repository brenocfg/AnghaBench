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
typedef  int uint ;

/* Variables and functions */
 scalar_t__ FLAG_S ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int m68ki_get_sr () ; 
 int /*<<< orphan*/  m68ki_set_sr (int) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_eori_16_tos(void)
{
	if(FLAG_S)
	{
		uint src = OPER_I_16();
		m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
		m68ki_set_sr(m68ki_get_sr() ^ src);
		return;
	}
	m68ki_exception_privilege_violation();
}