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
 int EA_AX_PD_32 () ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int OPER_AW_32 () ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  m68ki_write_16 (int,int) ; 

__attribute__((used)) static void m68k_op_move_32_pd_aw(void)
{
  uint res = OPER_AW_32();
  uint ea = EA_AX_PD_32();

  FLAG_N = NFLAG_32(res);
  FLAG_Z = res;
  FLAG_V = VFLAG_CLEAR;
  FLAG_C = CFLAG_CLEAR;

  m68ki_write_16(ea+2, res & 0xFFFF );
  m68ki_write_16(ea, (res >> 16) & 0xFFFF );
}