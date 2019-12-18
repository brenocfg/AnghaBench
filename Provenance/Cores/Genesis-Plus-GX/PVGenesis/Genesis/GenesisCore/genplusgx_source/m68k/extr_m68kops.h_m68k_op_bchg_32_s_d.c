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
 int DY ; 
 int FLAG_Z ; 
 int OPER_I_8 () ; 

__attribute__((used)) static void m68k_op_bchg_32_s_d(void)
{
  uint* r_dst = &DY;
  uint mask = 1 << (OPER_I_8() & 0x1f);

  FLAG_Z = *r_dst & mask;
  *r_dst ^= mask;
}