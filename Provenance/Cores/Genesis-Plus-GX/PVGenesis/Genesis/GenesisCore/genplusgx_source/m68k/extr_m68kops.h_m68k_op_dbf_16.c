#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_3__ {scalar_t__ detected; } ;
struct TYPE_4__ {TYPE_1__ poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYC_DBCC_F_EXP ; 
 int /*<<< orphan*/  CYC_DBCC_F_NOEXP ; 
 int DY ; 
 int MASK_OUT_ABOVE_16 (int) ; 
 int MASK_OUT_BELOW_16 (int) ; 
 int OPER_I_16 () ; 
 int REG_PC ; 
 int /*<<< orphan*/  USE_CYCLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_branch_16 (int) ; 
 TYPE_2__ m68ki_cpu ; 

__attribute__((used)) static void m68k_op_dbf_16(void)
{
  uint* r_dst = &DY;
  uint res = MASK_OUT_ABOVE_16(*r_dst - 1);
  *r_dst = MASK_OUT_BELOW_16(*r_dst) | res;

  /* reset idle loop detection */
  m68ki_cpu.poll.detected = 0;

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
}