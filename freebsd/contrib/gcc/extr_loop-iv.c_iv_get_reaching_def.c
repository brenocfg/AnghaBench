#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct df_ref {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum iv_grd_result { ____Placeholder_iv_grd_result } iv_grd_result ;
typedef  scalar_t__ basic_block ;
struct TYPE_2__ {struct df_ref* ref; scalar_t__ next; } ;

/* Variables and functions */
 scalar_t__ BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ DF_INSN_LUID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DF_REF_BB (struct df_ref*) ; 
 TYPE_1__* DF_REF_CHAIN (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_INSN (struct df_ref*) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GRD_INVALID ; 
 int GRD_INVARIANT ; 
 int GRD_MAYBE_BIV ; 
 int GRD_SINGLE_DOM ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_loop ; 
 int /*<<< orphan*/  df ; 
 struct df_ref* df_find_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dominated_by_p (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ just_once_each_iteration_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  simple_reg_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum iv_grd_result
iv_get_reaching_def (rtx insn, rtx reg, struct df_ref **def)
{
  struct df_ref *use, *adef;
  basic_block def_bb, use_bb;
  rtx def_insn;
  bool dom_p;
  
  *def = NULL;
  if (!simple_reg_p (reg))
    return GRD_INVALID;
  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);
  gcc_assert (REG_P (reg));

  use = df_find_use (df, insn, reg);
  gcc_assert (use != NULL);

  if (!DF_REF_CHAIN (use))
    return GRD_INVARIANT;

  /* More than one reaching def.  */
  if (DF_REF_CHAIN (use)->next)
    return GRD_INVALID;

  adef = DF_REF_CHAIN (use)->ref;
  def_insn = DF_REF_INSN (adef);
  def_bb = DF_REF_BB (adef);
  use_bb = BLOCK_FOR_INSN (insn);

  if (use_bb == def_bb)
    dom_p = (DF_INSN_LUID (df, def_insn) < DF_INSN_LUID (df, insn));
  else
    dom_p = dominated_by_p (CDI_DOMINATORS, use_bb, def_bb);

  if (dom_p)
    {
      *def = adef;
      return GRD_SINGLE_DOM;
    }

  /* The definition does not dominate the use.  This is still OK if
     this may be a use of a biv, i.e. if the def_bb dominates loop
     latch.  */
  if (just_once_each_iteration_p (current_loop, def_bb))
    return GRD_MAYBE_BIV;

  return GRD_INVALID;
}