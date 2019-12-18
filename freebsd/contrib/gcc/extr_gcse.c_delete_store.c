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
struct ls_expr {scalar_t__ reaching_reg; int /*<<< orphan*/  pattern; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ AVAIL_STORE_LIST (struct ls_expr*) ; 
 int /*<<< orphan*/  BLOCK_FOR_INSN (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_store_insn (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct ls_expr*) ; 

__attribute__((used)) static void
delete_store (struct ls_expr * expr, basic_block bb)
{
  rtx reg, i, del;

  if (expr->reaching_reg == NULL_RTX)
    expr->reaching_reg = gen_reg_rtx (GET_MODE (expr->pattern));

  reg = expr->reaching_reg;

  for (i = AVAIL_STORE_LIST (expr); i; i = XEXP (i, 1))
    {
      del = XEXP (i, 0);
      if (BLOCK_FOR_INSN (del) == bb)
	{
	  /* We know there is only one since we deleted redundant
	     ones during the available computation.  */
	  replace_store_insn (reg, del, bb, expr);
	  break;
	}
    }
}