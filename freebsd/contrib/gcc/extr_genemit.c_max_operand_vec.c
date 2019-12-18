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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int max_dup_opno ; 
 int /*<<< orphan*/  max_operand_1 (int /*<<< orphan*/ ) ; 
 int max_opno ; 
 int max_scratch_opno ; 

__attribute__((used)) static int
max_operand_vec (rtx insn, int arg)
{
  int len = XVECLEN (insn, arg);
  int i;

  max_opno = -1;
  max_dup_opno = -1;
  max_scratch_opno = -1;

  for (i = 0; i < len; i++)
    max_operand_1 (XVECEXP (insn, arg, i));

  return max_opno + 1;
}