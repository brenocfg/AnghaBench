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
 int EA_AY_DI_16 () ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int m68ki_read_8 (int) ; 

__attribute__((used)) static void m68k_op_movep_16_er(void)
{
  uint ea = EA_AY_DI_16();
  uint* r_dst = &DX;

  *r_dst = MASK_OUT_BELOW_16(*r_dst) | ((m68ki_read_8(ea) << 8) + m68ki_read_8(ea + 2));
}