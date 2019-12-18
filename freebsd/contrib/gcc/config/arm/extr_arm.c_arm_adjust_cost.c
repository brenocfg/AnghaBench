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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;
struct TYPE_2__ {int n_operands; scalar_t__* operand_type; int /*<<< orphan*/ ** operand; } ;

/* Variables and functions */
 scalar_t__ CALL_INSN ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ MEM ; 
 scalar_t__ OP_IN ; 
 scalar_t__ REG_DEP_ANTI ; 
 scalar_t__ REG_DEP_OUTPUT ; 
 scalar_t__ REG_NOTE_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
 scalar_t__ SYMBOL_REF ; 
 int TYPE_ALU_SHIFT ; 
 int TYPE_ALU_SHIFT_REG ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ arm_tune_xscale ; 
 int /*<<< orphan*/  extract_insn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int get_attr_shift (int /*<<< orphan*/ *) ; 
 int get_attr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  preprocess_constraints () ; 
 TYPE_1__ recog_data ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ *) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static int
arm_adjust_cost (rtx insn, rtx link, rtx dep, int cost)
{
  rtx i_pat, d_pat;

  /* Some true dependencies can have a higher cost depending
     on precisely how certain input operands are used.  */
  if (arm_tune_xscale
      && REG_NOTE_KIND (link) == 0
      && recog_memoized (insn) >= 0
      && recog_memoized (dep) >= 0)
    {
      int shift_opnum = get_attr_shift (insn);
      enum attr_type attr_type = get_attr_type (dep);

      /* If nonzero, SHIFT_OPNUM contains the operand number of a shifted
	 operand for INSN.  If we have a shifted input operand and the
	 instruction we depend on is another ALU instruction, then we may
	 have to account for an additional stall.  */
      if (shift_opnum != 0
	  && (attr_type == TYPE_ALU_SHIFT || attr_type == TYPE_ALU_SHIFT_REG))
	{
	  rtx shifted_operand;
	  int opno;

	  /* Get the shifted operand.  */
	  extract_insn (insn);
	  shifted_operand = recog_data.operand[shift_opnum];

	  /* Iterate over all the operands in DEP.  If we write an operand
	     that overlaps with SHIFTED_OPERAND, then we have increase the
	     cost of this dependency.  */
	  extract_insn (dep);
	  preprocess_constraints ();
	  for (opno = 0; opno < recog_data.n_operands; opno++)
	    {
	      /* We can ignore strict inputs.  */
	      if (recog_data.operand_type[opno] == OP_IN)
		continue;

	      if (reg_overlap_mentioned_p (recog_data.operand[opno],
					   shifted_operand))
		return 2;
	    }
	}
    }

  /* XXX This is not strictly true for the FPA.  */
  if (REG_NOTE_KIND (link) == REG_DEP_ANTI
      || REG_NOTE_KIND (link) == REG_DEP_OUTPUT)
    return 0;

  /* Call insns don't incur a stall, even if they follow a load.  */
  if (REG_NOTE_KIND (link) == 0
      && GET_CODE (insn) == CALL_INSN)
    return 1;

  if ((i_pat = single_set (insn)) != NULL
      && GET_CODE (SET_SRC (i_pat)) == MEM
      && (d_pat = single_set (dep)) != NULL
      && GET_CODE (SET_DEST (d_pat)) == MEM)
    {
      rtx src_mem = XEXP (SET_SRC (i_pat), 0);
      /* This is a load after a store, there is no conflict if the load reads
	 from a cached area.  Assume that loads from the stack, and from the
	 constant pool are cached, and that others will miss.  This is a
	 hack.  */

      if ((GET_CODE (src_mem) == SYMBOL_REF && CONSTANT_POOL_ADDRESS_P (src_mem))
	  || reg_mentioned_p (stack_pointer_rtx, src_mem)
	  || reg_mentioned_p (frame_pointer_rtx, src_mem)
	  || reg_mentioned_p (hard_frame_pointer_rtx, src_mem))
	return 1;
    }

  return cost;
}