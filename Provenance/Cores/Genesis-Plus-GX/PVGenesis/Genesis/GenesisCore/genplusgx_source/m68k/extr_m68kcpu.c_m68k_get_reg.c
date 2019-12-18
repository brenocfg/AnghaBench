#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int m68k_register_t ;
struct TYPE_2__ {unsigned int* dar; int t1_flag; int s_flag; int int_mask; int x_flag; int n_flag; int v_flag; int c_flag; unsigned int* sp; unsigned int pref_addr; unsigned int pref_data; unsigned int ir; int /*<<< orphan*/  not_z_flag; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int CFLAG_SET ; 
#define  M68K_REG_A0 151 
#define  M68K_REG_A1 150 
#define  M68K_REG_A2 149 
#define  M68K_REG_A3 148 
#define  M68K_REG_A4 147 
#define  M68K_REG_A5 146 
#define  M68K_REG_A6 145 
#define  M68K_REG_A7 144 
#define  M68K_REG_D0 143 
#define  M68K_REG_D1 142 
#define  M68K_REG_D2 141 
#define  M68K_REG_D3 140 
#define  M68K_REG_D4 139 
#define  M68K_REG_D5 138 
#define  M68K_REG_D6 137 
#define  M68K_REG_D7 136 
#define  M68K_REG_IR 135 
#define  M68K_REG_ISP 134 
#define  M68K_REG_PC 133 
#define  M68K_REG_PREF_ADDR 132 
#define  M68K_REG_PREF_DATA 131 
#define  M68K_REG_SP 130 
#define  M68K_REG_SR 129 
#define  M68K_REG_USP 128 
 unsigned int MASK_OUT_ABOVE_32 (int /*<<< orphan*/ ) ; 
 int NFLAG_SET ; 
 int VFLAG_SET ; 
 int XFLAG_SET ; 
 TYPE_1__ m68ki_cpu ; 

unsigned int m68k_get_reg(m68k_register_t regnum)
{
  switch(regnum)
  {
    case M68K_REG_D0:  return m68ki_cpu.dar[0];
    case M68K_REG_D1:  return m68ki_cpu.dar[1];
    case M68K_REG_D2:  return m68ki_cpu.dar[2];
    case M68K_REG_D3:  return m68ki_cpu.dar[3];
    case M68K_REG_D4:  return m68ki_cpu.dar[4];
    case M68K_REG_D5:  return m68ki_cpu.dar[5];
    case M68K_REG_D6:  return m68ki_cpu.dar[6];
    case M68K_REG_D7:  return m68ki_cpu.dar[7];
    case M68K_REG_A0:  return m68ki_cpu.dar[8];
    case M68K_REG_A1:  return m68ki_cpu.dar[9];
    case M68K_REG_A2:  return m68ki_cpu.dar[10];
    case M68K_REG_A3:  return m68ki_cpu.dar[11];
    case M68K_REG_A4:  return m68ki_cpu.dar[12];
    case M68K_REG_A5:  return m68ki_cpu.dar[13];
    case M68K_REG_A6:  return m68ki_cpu.dar[14];
    case M68K_REG_A7:  return m68ki_cpu.dar[15];
    case M68K_REG_PC:  return MASK_OUT_ABOVE_32(m68ki_cpu.pc);
    case M68K_REG_SR:  return  m68ki_cpu.t1_flag        |
                  (m68ki_cpu.s_flag << 11)              |
                   m68ki_cpu.int_mask                   |
                  ((m68ki_cpu.x_flag & XFLAG_SET) >> 4) |
                  ((m68ki_cpu.n_flag & NFLAG_SET) >> 4) |
                  ((!m68ki_cpu.not_z_flag) << 2)        |
                  ((m68ki_cpu.v_flag & VFLAG_SET) >> 6) |
                  ((m68ki_cpu.c_flag & CFLAG_SET) >> 8);
    case M68K_REG_SP:  return m68ki_cpu.dar[15];
    case M68K_REG_USP:  return m68ki_cpu.s_flag ? m68ki_cpu.sp[0] : m68ki_cpu.dar[15];
    case M68K_REG_ISP:  return m68ki_cpu.s_flag ? m68ki_cpu.dar[15] : m68ki_cpu.sp[4];
#if M68K_EMULATE_PREFETCH
    case M68K_REG_PREF_ADDR:  return m68ki_cpu.pref_addr;
    case M68K_REG_PREF_DATA:  return m68ki_cpu.pref_data;
#endif
    case M68K_REG_IR:  return m68ki_cpu.ir;
    default:      return 0;
  }
}