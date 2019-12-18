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
 void* CPU_PREF_ADDR ; 
 int /*<<< orphan*/  FLAG_S ; 
#define  M68K_REG_A0 150 
#define  M68K_REG_A1 149 
#define  M68K_REG_A2 148 
#define  M68K_REG_A3 147 
#define  M68K_REG_A4 146 
#define  M68K_REG_A5 145 
#define  M68K_REG_A6 144 
#define  M68K_REG_A7 143 
#define  M68K_REG_D0 142 
#define  M68K_REG_D1 141 
#define  M68K_REG_D2 140 
#define  M68K_REG_D3 139 
#define  M68K_REG_D4 138 
#define  M68K_REG_D5 137 
#define  M68K_REG_D6 136 
#define  M68K_REG_D7 135 
#define  M68K_REG_IR 134 
#define  M68K_REG_ISP 133 
#define  M68K_REG_PC 132 
#define  M68K_REG_PREF_ADDR 131 
#define  M68K_REG_SP 130 
#define  M68K_REG_SR 129 
#define  M68K_REG_USP 128 
 int /*<<< orphan*/  MASK_OUT_ABOVE_16 (unsigned int) ; 
 void* MASK_OUT_ABOVE_32 (unsigned int) ; 
 void** REG_A ; 
 void** REG_D ; 
 int /*<<< orphan*/  REG_IR ; 
 void* REG_ISP ; 
 void* REG_SP ; 
 void* REG_USP ; 
 int /*<<< orphan*/  m68ki_jump (void*) ; 
 int /*<<< orphan*/  m68ki_set_sr (unsigned int) ; 

void s68k_set_reg(m68k_register_t regnum, unsigned int value)
{
  switch(regnum)
  {
    case M68K_REG_D0:  REG_D[0] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D1:  REG_D[1] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D2:  REG_D[2] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D3:  REG_D[3] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D4:  REG_D[4] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D5:  REG_D[5] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D6:  REG_D[6] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_D7:  REG_D[7] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A0:  REG_A[0] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A1:  REG_A[1] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A2:  REG_A[2] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A3:  REG_A[3] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A4:  REG_A[4] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A5:  REG_A[5] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A6:  REG_A[6] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_A7:  REG_A[7] = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_PC:  m68ki_jump(MASK_OUT_ABOVE_32(value)); return;
    case M68K_REG_SR:  m68ki_set_sr(value); return;
    case M68K_REG_SP:  REG_SP = MASK_OUT_ABOVE_32(value); return;
    case M68K_REG_USP:  if(FLAG_S)
                REG_USP = MASK_OUT_ABOVE_32(value);
              else
                REG_SP = MASK_OUT_ABOVE_32(value);
              return;
    case M68K_REG_ISP:  if(FLAG_S)
                REG_SP = MASK_OUT_ABOVE_32(value);
              else
                REG_ISP = MASK_OUT_ABOVE_32(value);
              return;
    case M68K_REG_IR:  REG_IR = MASK_OUT_ABOVE_16(value); return;
#if M68K_EMULATE_PREFETCH
    case M68K_REG_PREF_ADDR:  CPU_PREF_ADDR = MASK_OUT_ABOVE_32(value); return;
#endif
    default:      return;
  }
}