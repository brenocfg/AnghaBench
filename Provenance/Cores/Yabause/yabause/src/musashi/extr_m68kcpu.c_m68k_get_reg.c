#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* dar; int t1_flag; int t0_flag; int s_flag; int m_flag; int int_mask; int x_flag; int n_flag; int v_flag; int c_flag; unsigned int* sp; unsigned int sfc; unsigned int dfc; unsigned int vbr; unsigned int cacr; unsigned int caar; unsigned int pref_addr; unsigned int pref_data; unsigned int ir; int /*<<< orphan*/  cpu_type; int /*<<< orphan*/  ppc; int /*<<< orphan*/  not_z_flag; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ m68ki_cpu_core ;
typedef  int m68k_register_t ;

/* Variables and functions */
 int CFLAG_SET ; 
#define  CPU_TYPE_000 163 
#define  CPU_TYPE_010 162 
#define  CPU_TYPE_020 161 
#define  CPU_TYPE_EC020 160 
 scalar_t__ M68K_CPU_TYPE_68000 ; 
 scalar_t__ M68K_CPU_TYPE_68010 ; 
 scalar_t__ M68K_CPU_TYPE_68020 ; 
 scalar_t__ M68K_CPU_TYPE_68EC020 ; 
 unsigned int M68K_CPU_TYPE_INVALID ; 
#define  M68K_REG_A0 159 
#define  M68K_REG_A1 158 
#define  M68K_REG_A2 157 
#define  M68K_REG_A3 156 
#define  M68K_REG_A4 155 
#define  M68K_REG_A5 154 
#define  M68K_REG_A6 153 
#define  M68K_REG_A7 152 
#define  M68K_REG_CAAR 151 
#define  M68K_REG_CACR 150 
#define  M68K_REG_CPU_TYPE 149 
#define  M68K_REG_D0 148 
#define  M68K_REG_D1 147 
#define  M68K_REG_D2 146 
#define  M68K_REG_D3 145 
#define  M68K_REG_D4 144 
#define  M68K_REG_D5 143 
#define  M68K_REG_D6 142 
#define  M68K_REG_D7 141 
#define  M68K_REG_DFC 140 
#define  M68K_REG_IR 139 
#define  M68K_REG_ISP 138 
#define  M68K_REG_MSP 137 
#define  M68K_REG_PC 136 
#define  M68K_REG_PPC 135 
#define  M68K_REG_PREF_ADDR 134 
#define  M68K_REG_PREF_DATA 133 
#define  M68K_REG_SFC 132 
#define  M68K_REG_SP 131 
#define  M68K_REG_SR 130 
#define  M68K_REG_USP 129 
#define  M68K_REG_VBR 128 
 unsigned int MASK_OUT_ABOVE_32 (int /*<<< orphan*/ ) ; 
 int NFLAG_SET ; 
 int VFLAG_SET ; 
 int XFLAG_SET ; 
 TYPE_1__ m68ki_cpu ; 

unsigned int m68k_get_reg(void* context, m68k_register_t regnum)
{
	m68ki_cpu_core* cpu = context != NULL ?(m68ki_cpu_core*)context : &m68ki_cpu;

	switch(regnum)
	{
		case M68K_REG_D0:	return cpu->dar[0];
		case M68K_REG_D1:	return cpu->dar[1];
		case M68K_REG_D2:	return cpu->dar[2];
		case M68K_REG_D3:	return cpu->dar[3];
		case M68K_REG_D4:	return cpu->dar[4];
		case M68K_REG_D5:	return cpu->dar[5];
		case M68K_REG_D6:	return cpu->dar[6];
		case M68K_REG_D7:	return cpu->dar[7];
		case M68K_REG_A0:	return cpu->dar[8];
		case M68K_REG_A1:	return cpu->dar[9];
		case M68K_REG_A2:	return cpu->dar[10];
		case M68K_REG_A3:	return cpu->dar[11];
		case M68K_REG_A4:	return cpu->dar[12];
		case M68K_REG_A5:	return cpu->dar[13];
		case M68K_REG_A6:	return cpu->dar[14];
		case M68K_REG_A7:	return cpu->dar[15];
		case M68K_REG_PC:	return MASK_OUT_ABOVE_32(cpu->pc);
		case M68K_REG_SR:	return	cpu->t1_flag						|
									cpu->t0_flag						|
									(cpu->s_flag << 11)					|
									(cpu->m_flag << 11)					|
									cpu->int_mask						|
									((cpu->x_flag & XFLAG_SET) >> 4)	|
									((cpu->n_flag & NFLAG_SET) >> 4)	|
									((!cpu->not_z_flag) << 2)			|
									((cpu->v_flag & VFLAG_SET) >> 6)	|
									((cpu->c_flag & CFLAG_SET) >> 8);
		case M68K_REG_SP:	return cpu->dar[15];
		case M68K_REG_USP:	return cpu->s_flag ? cpu->sp[0] : cpu->dar[15];
		case M68K_REG_ISP:	return cpu->s_flag && !cpu->m_flag ? cpu->dar[15] : cpu->sp[4];
		case M68K_REG_MSP:	return cpu->s_flag && cpu->m_flag ? cpu->dar[15] : cpu->sp[6];
		case M68K_REG_SFC:	return cpu->sfc;
		case M68K_REG_DFC:	return cpu->dfc;
		case M68K_REG_VBR:	return cpu->vbr;
		case M68K_REG_CACR:	return cpu->cacr;
		case M68K_REG_CAAR:	return cpu->caar;
		case M68K_REG_PREF_ADDR:	return cpu->pref_addr;
		case M68K_REG_PREF_DATA:	return cpu->pref_data;
		case M68K_REG_PPC:	return MASK_OUT_ABOVE_32(cpu->ppc);
		case M68K_REG_IR:	return cpu->ir;
		case M68K_REG_CPU_TYPE:
			switch(cpu->cpu_type)
			{
				case CPU_TYPE_000:		return (unsigned int)M68K_CPU_TYPE_68000;
				case CPU_TYPE_010:		return (unsigned int)M68K_CPU_TYPE_68010;
				case CPU_TYPE_EC020:	return (unsigned int)M68K_CPU_TYPE_68EC020;
				case CPU_TYPE_020:		return (unsigned int)M68K_CPU_TYPE_68020;
			}
			return M68K_CPU_TYPE_INVALID;
		default:			return 0;
	}
	return 0;
}