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
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;

/* Variables and functions */
#define  RELOAD_FOR_INPADDR_ADDRESS 138 
#define  RELOAD_FOR_INPUT 137 
#define  RELOAD_FOR_INPUT_ADDRESS 136 
#define  RELOAD_FOR_INSN 135 
#define  RELOAD_FOR_OPADDR_ADDR 134 
#define  RELOAD_FOR_OPERAND_ADDRESS 133 
#define  RELOAD_FOR_OTHER_ADDRESS 132 
#define  RELOAD_FOR_OUTADDR_ADDRESS 131 
#define  RELOAD_FOR_OUTPUT 130 
#define  RELOAD_FOR_OUTPUT_ADDRESS 129 
#define  RELOAD_OTHER 128 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int reload_n_operands ; 
 int /*<<< orphan*/  reload_reg_unavailable ; 
 int /*<<< orphan*/  reload_reg_used ; 
 int /*<<< orphan*/ * reload_reg_used_in_inpaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_input ; 
 int /*<<< orphan*/ * reload_reg_used_in_input_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_insn ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr_reload ; 
 int /*<<< orphan*/  reload_reg_used_in_other_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_outaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_output ; 
 int /*<<< orphan*/ * reload_reg_used_in_output_addr ; 

__attribute__((used)) static int
reload_reg_free_p (unsigned int regno, int opnum, enum reload_type type)
{
  int i;

  /* In use for a RELOAD_OTHER means it's not available for anything.  */
  if (TEST_HARD_REG_BIT (reload_reg_used, regno)
      || TEST_HARD_REG_BIT (reload_reg_unavailable, regno))
    return 0;

  switch (type)
    {
    case RELOAD_OTHER:
      /* In use for anything means we can't use it for RELOAD_OTHER.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_other_addr, regno)
	  || TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno)
	  || TEST_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, regno)
	  || TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno))
	return 0;

      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_INPUT:
      if (TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	  || TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno))
	return 0;

      if (TEST_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, regno))
	return 0;

      /* If it is used for some other input, can't use it.  */
      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      /* If it is used in a later operand's address, can't use it.  */
      for (i = opnum + 1; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_INPUT_ADDRESS:
      /* Can't use a register if it is used for an input address for this
	 operand or used as an input in an earlier one.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[opnum], regno)
	  || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[opnum], regno))
	return 0;

      for (i = 0; i < opnum; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_INPADDR_ADDRESS:
      /* Can't use a register if it is used for an input address
	 for this operand or used as an input in an earlier
	 one.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[opnum], regno))
	return 0;

      for (i = 0; i < opnum; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_OUTPUT_ADDRESS:
      /* Can't use a register if it is used for an output address for this
	 operand or used as an output in this or a later operand.  Note
	 that multiple output operands are emitted in reverse order, so
	 the conflicting ones are those with lower indices.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[opnum], regno))
	return 0;

      for (i = 0; i <= opnum; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_OUTADDR_ADDRESS:
      /* Can't use a register if it is used for an output address
	 for this operand or used as an output in this or a
	 later operand.  Note that multiple output operands are
	 emitted in reverse order, so the conflicting ones are
	 those with lower indices.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[opnum], regno))
	return 0;

      for (i = 0; i <= opnum; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_OPERAND_ADDRESS:
      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      return (! TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	      && ! TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno));

    case RELOAD_FOR_OPADDR_ADDR:
      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      return (!TEST_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, regno));

    case RELOAD_FOR_OUTPUT:
      /* This cannot share a register with RELOAD_FOR_INSN reloads, other
	 outputs, or an operand address for this or an earlier output.
	 Note that multiple output operands are emitted in reverse order,
	 so the conflicting ones are those with higher indices.  */
      if (TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno))
	return 0;

      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      for (i = opnum; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno))
	  return 0;

      return 1;

    case RELOAD_FOR_INSN:
      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return (! TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	      && ! TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno));

    case RELOAD_FOR_OTHER_ADDRESS:
      return ! TEST_HARD_REG_BIT (reload_reg_used_in_other_addr, regno);

    default:
      gcc_unreachable ();
    }
}