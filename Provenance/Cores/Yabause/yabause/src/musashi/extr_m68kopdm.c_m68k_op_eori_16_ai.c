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
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int EA_AY_AI_16 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int /*<<< orphan*/  NFLAG_16 (int) ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int m68ki_read_16 (int) ; 
 int /*<<< orphan*/  m68ki_write_16 (int,int) ; 

void m68k_op_eori_16_ai(void)
{
	uint src = OPER_I_16();
	uint ea = EA_AY_AI_16();
	uint res = src ^ m68ki_read_16(ea);

	m68ki_write_16(ea, res);

	FLAG_N = NFLAG_16(res);
	FLAG_Z = res;
	FLAG_C = CFLAG_CLEAR;
	FLAG_V = VFLAG_CLEAR;
}