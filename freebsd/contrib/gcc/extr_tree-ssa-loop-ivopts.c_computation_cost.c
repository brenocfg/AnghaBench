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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int LAST_VIRTUAL_REGISTER ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ address_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  prepare_decl_rtl ; 
 unsigned int seq_cost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int /*<<< orphan*/  walk_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned
computation_cost (tree expr)
{
  rtx seq, rslt;
  tree type = TREE_TYPE (expr);
  unsigned cost;
  /* Avoid using hard regs in ways which may be unsupported.  */
  int regno = LAST_VIRTUAL_REGISTER + 1;

  walk_tree (&expr, prepare_decl_rtl, &regno, NULL);
  start_sequence ();
  rslt = expand_expr (expr, NULL_RTX, TYPE_MODE (type), EXPAND_NORMAL);
  seq = get_insns ();
  end_sequence ();

  cost = seq_cost (seq);
  if (MEM_P (rslt))
    cost += address_cost (XEXP (rslt, 0), TYPE_MODE (type));

  return cost;
}