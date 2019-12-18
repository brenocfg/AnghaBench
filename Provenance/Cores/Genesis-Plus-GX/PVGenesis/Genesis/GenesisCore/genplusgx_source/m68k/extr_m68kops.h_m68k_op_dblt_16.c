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
 scalar_t__ COND_NOT_LT () ; 
 int /*<<< orphan*/  CYC_DBCC_F_EXP ; 
 int /*<<< orphan*/  CYC_DBCC_F_NOEXP ; 
 int DY ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int OPER_I_16 () ; 
 int REG_PC ; 
 int /*<<< orphan*/  USE_CYCLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_branch_16 (int) ; 

__attribute__((used)) static void m68k_op_dblt_16(void)
{
  if(COND_NOT_LT())
  {
    uint* r_dst = &DY;
    uint res = MASK_OUT_ABOVE_16(*r_dst - 1);

    *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;
    if(res != 0xffff)
    {
      uint offset = OPER_I_16();
      REG_PC -= 2;
      m68ki_branch_16(offset);
      USE_CYCLES(CYC_DBCC_F_NOEXP);
      return;
    }
    REG_PC += 2;
    USE_CYCLES(CYC_DBCC_F_EXP);
    return;
  }
  REG_PC += 2;
}