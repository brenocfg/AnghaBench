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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  OPER_I_16 () ; 
 int REG_PC ; 
 int /*<<< orphan*/  m68ki_branch_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_push_32 (int) ; 

__attribute__((used)) static void m68k_op_bsr_16(void)
{
  uint offset = OPER_I_16();
  m68ki_push_32(REG_PC);
  REG_PC -= 2;
  m68ki_branch_16(offset);
}