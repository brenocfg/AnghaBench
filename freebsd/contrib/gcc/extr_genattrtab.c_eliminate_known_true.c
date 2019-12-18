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
 scalar_t__ AND ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMPLIFY_TEST_EXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simplify_and_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static rtx
eliminate_known_true (rtx known_true, rtx exp, int insn_code, int insn_index)
{
  rtx term;

  known_true = SIMPLIFY_TEST_EXP (known_true, insn_code, insn_index);

  if (GET_CODE (known_true) == AND)
    {
      exp = eliminate_known_true (XEXP (known_true, 0), exp,
				  insn_code, insn_index);
      exp = eliminate_known_true (XEXP (known_true, 1), exp,
				  insn_code, insn_index);
    }
  else
    {
      term = known_true;
      exp = simplify_and_tree (exp, &term, insn_code, insn_index);
    }

  return exp;
}