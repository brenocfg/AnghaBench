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
 int DX ; 
 int EA_AW_8 () ; 
 int FLAG_Z ; 
 int m68ki_read_8 (int) ; 
 int /*<<< orphan*/  m68ki_write_8 (int,int) ; 

void m68k_op_bchg_8_r_aw(void)
{
	uint ea = EA_AW_8();
	uint src = m68ki_read_8(ea);
	uint mask = 1 << (DX & 7);

	FLAG_Z = src & mask;
	m68ki_write_8(ea, src ^ mask);
}