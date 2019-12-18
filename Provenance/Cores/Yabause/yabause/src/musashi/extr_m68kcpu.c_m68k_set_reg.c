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
typedef  int m68k_register_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_M ; 
 int /*<<< orphan*/  FLAG_S ; 
#define  M68K_REG_A0 157 
#define  M68K_REG_A1 156 
#define  M68K_REG_A2 155 
#define  M68K_REG_A3 154 
#define  M68K_REG_A4 153 
#define  M68K_REG_A5 152 
#define  M68K_REG_A6 151 
#define  M68K_REG_A7 150 
#define  M68K_REG_CAAR 149 
#define  M68K_REG_CACR 148 
#define  M68K_REG_CPU_TYPE 147 
#define  M68K_REG_D0 146 
#define  M68K_REG_D1 145 
#define  M68K_REG_D2 144 
#define  M68K_REG_D3 143 
#define  M68K_REG_D4 142 
#define  M68K_REG_D5 141 
#define  M68K_REG_D6 140 
#define  M68K_REG_D7 139 
#define  M68K_REG_DFC 138 
#define  M68K_REG_IR 137 
#define  M68K_REG_ISP 136 
#define  M68K_REG_MSP 135 
#define  M68K_REG_PC 134 
#define  M68K_REG_PPC 133 
#define  M68K_REG_SFC 132 
#define  M68K_REG_SP 131 
#define  M68K_REG_SR 130 
#define  M68K_REG_USP 129 
#define  M68K_REG_VBR 128 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (unsigned int) ; 
 void* MASK_OUT_ABOVE_32 (unsigned int) ; 
 void** REG_A ; 
 void* REG_CAAR ; 
 void* REG_CACR ; 
 void** REG_D ; 
 unsigned int REG_DFC ; 
 int /*<<< orphan*/  REG_IR ; 
 void* REG_ISP ; 
 void* REG_MSP ; 
 void* REG_PPC ; 
 unsigned int REG_SFC ; 
 void* REG_SP ; 
 void* REG_USP ; 
 void* REG_VBR ; 
 int /*<<< orphan*/  m68k_set_cpu_type (unsigned int) ; 
 int /*<<< orphan*/  m68ki_jump (void*) ; 
 int /*<<< orphan*/  m68ki_set_sr (unsigned int) ; 

void m68k_set_reg(m68k_register_t regnum, unsigned int value)
{
	switch(regnum)
	{
		case M68K_REG_D0:	REG_D[0] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D1:	REG_D[1] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D2:	REG_D[2] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D3:	REG_D[3] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D4:	REG_D[4] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D5:	REG_D[5] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D6:	REG_D[6] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_D7:	REG_D[7] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A0:	REG_A[0] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A1:	REG_A[1] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A2:	REG_A[2] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A3:	REG_A[3] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A4:	REG_A[4] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A5:	REG_A[5] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A6:	REG_A[6] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_A7:	REG_A[7] = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_PC:	m68ki_jump(MASK_OUT_ABOVE_32(value)); return;
		case M68K_REG_SR:	m68ki_set_sr(value); return;
		case M68K_REG_SP:	REG_SP = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_USP:	if(FLAG_S)
								REG_USP = MASK_OUT_ABOVE_32(value);
							else
								REG_SP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_ISP:	if(FLAG_S && !FLAG_M)
								REG_SP = MASK_OUT_ABOVE_32(value);
							else
								REG_ISP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_MSP:	if(FLAG_S && FLAG_M)
								REG_SP = MASK_OUT_ABOVE_32(value);
							else
								REG_MSP = MASK_OUT_ABOVE_32(value);
							return;
		case M68K_REG_VBR:	REG_VBR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_SFC:	REG_SFC = value & 7; return;
		case M68K_REG_DFC:	REG_DFC = value & 7; return;
		case M68K_REG_CACR:	REG_CACR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_CAAR:	REG_CAAR = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_PPC:	REG_PPC = MASK_OUT_ABOVE_32(value); return;
		case M68K_REG_IR:	REG_IR = MASK_OUT_ABOVE_16(value); return;
		case M68K_REG_CPU_TYPE: m68k_set_cpu_type(value); return;
		default:			return;
	}
}