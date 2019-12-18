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
 int EA_A7_PD_8 () ; 
 int FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int FLAG_V ; 
 int FLAG_X ; 
 int FLAG_Z ; 
 scalar_t__ HIGH_NIBBLE (int) ; 
 int LOW_NIBBLE (int) ; 
 int MASK_OUT_ABOVE_8 (int) ; 
 int /*<<< orphan*/  NFLAG_8 (int) ; 
 int OPER_A7_PD_8 () ; 
 int XFLAG_AS_1 () ; 
 int m68ki_read_8 (int) ; 
 int /*<<< orphan*/  m68ki_write_8 (int,int) ; 

void m68k_op_sbcd_8_mm_axy7(void)
{
	uint src = OPER_A7_PD_8();
	uint ea  = EA_A7_PD_8();
	uint dst = m68ki_read_8(ea);
	uint res = LOW_NIBBLE(dst) - LOW_NIBBLE(src) - XFLAG_AS_1();

	FLAG_V = ~res; /* Undefined V behavior */

	if(res > 9)
		res -= 6;
	res += HIGH_NIBBLE(dst) - HIGH_NIBBLE(src);
	FLAG_X = FLAG_C = (res > 0x99) << 8;
	if(FLAG_C)
		res += 0xa0;

	res = MASK_OUT_ABOVE_8(res);

	FLAG_V &= res; /* Undefined V behavior part II */
	FLAG_N = NFLAG_8(res); /* Undefined N behavior */
	FLAG_Z |= res;

	m68ki_write_8(ea, res);
}