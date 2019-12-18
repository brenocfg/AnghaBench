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
typedef  int sint ;

/* Variables and functions */
 scalar_t__ BIT_5 (int) ; 
 scalar_t__ BIT_B (int) ; 
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int EA_AY_DI_8 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int MAKE_INT_32 (int) ; 
 int MASK_OUT_ABOVE_32 (int) ; 
 int MASK_OUT_ABOVE_8 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int OPER_I_16 () ; 
 int* REG_D ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int m68ki_read_32 (int) ; 
 int m68ki_read_8 (int) ; 
 int /*<<< orphan*/  m68ki_write_32 (int,int) ; 
 int /*<<< orphan*/  m68ki_write_8 (int,int) ; 

void m68k_op_bfclr_32_di(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint word2 = OPER_I_16();
		sint offset = (word2>>6)&31;
		uint width = word2;
		uint mask_base;
		uint data_long;
		uint mask_long;
		uint data_byte = 0;
		uint mask_byte = 0;
		uint ea = EA_AY_DI_8();


		if(BIT_B(word2))
			offset = MAKE_INT_32(REG_D[offset&7]);
		if(BIT_5(word2))
			width = REG_D[width&7];

		/* Offset is signed so we have to use ugly math =( */
		ea += offset / 8;
		offset %= 8;
		if(offset < 0)
		{
			offset += 8;
			ea--;
		}
		width = ((width-1) & 31) + 1;

		mask_base = MASK_OUT_ABOVE_32(0xffffffff << (32 - width));
		mask_long = mask_base >> offset;

		data_long = m68ki_read_32(ea);
		FLAG_N = NFLAG_32(data_long << offset);
		FLAG_Z = data_long & mask_long;
		FLAG_V = VFLAG_CLEAR;
		FLAG_C = CFLAG_CLEAR;

		m68ki_write_32(ea, data_long & ~mask_long);

		if((width + offset) > 32)
		{
			mask_byte = MASK_OUT_ABOVE_8(mask_base);
			data_byte = m68ki_read_8(ea+4);
			FLAG_Z |= (data_byte & mask_byte);
			m68ki_write_8(ea+4, data_byte & ~mask_byte);
		}
		return;
	}
	m68ki_exception_illegal();
}