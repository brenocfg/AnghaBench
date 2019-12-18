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
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int reload_n_operands ; 
 int /*<<< orphan*/  reload_reg_used ; 
 int /*<<< orphan*/ * reload_reg_used_in_inpaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_input ; 
 int /*<<< orphan*/ * reload_reg_used_in_input_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_insn ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr ; 
 int /*<<< orphan*/  reload_reg_used_in_op_addr_reload ; 
 int /*<<< orphan*/ * reload_reg_used_in_outaddr_addr ; 
 int /*<<< orphan*/ * reload_reg_used_in_output ; 
 int /*<<< orphan*/ * reload_reg_used_in_output_addr ; 

__attribute__((used)) static int
reload_reg_reaches_end_p (unsigned int regno, int opnum, enum reload_type type)
{
  int i;

  switch (type)
    {
    case RELOAD_OTHER:
      /* Since a RELOAD_OTHER reload claims the reg for the entire insn,
	 its value must reach the end.  */
      return 1;

      /* If this use is for part of the insn,
	 its value reaches if no subsequent part uses the same register.
	 Just like the above function, don't try to do this with lots
	 of fallthroughs.  */

    case RELOAD_FOR_OTHER_ADDRESS:
      /* Here we check for everything else, since these don't conflict
	 with anything else and everything comes later.  */

      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      return (! TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno)
	      && ! TEST_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, regno)
	      && ! TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	      && ! TEST_HARD_REG_BIT (reload_reg_used, regno));

    case RELOAD_FOR_INPUT_ADDRESS:
    case RELOAD_FOR_INPADDR_ADDRESS:
      /* Similar, except that we check only for this and subsequent inputs
	 and the address of only subsequent inputs and we do not need
	 to check for RELOAD_OTHER objects since they are known not to
	 conflict.  */

      for (i = opnum; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      for (i = opnum + 1; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[i], regno))
	  return 0;

      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      if (TEST_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, regno))
	return 0;

      return (!TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno)
	      && !TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	      && !TEST_HARD_REG_BIT (reload_reg_used, regno));

    case RELOAD_FOR_INPUT:
      /* Similar to input address, except we start at the next operand for
	 both input and input address and we do not check for
	 RELOAD_FOR_OPERAND_ADDRESS and RELOAD_FOR_INSN since these
	 would conflict.  */

      for (i = opnum + 1; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_input_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_input[i], regno))
	  return 0;

      /* ... fall through ...  */

    case RELOAD_FOR_OPERAND_ADDRESS:
      /* Check outputs and their addresses.  */

      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return (!TEST_HARD_REG_BIT (reload_reg_used, regno));

    case RELOAD_FOR_OPADDR_ADDR:
      for (i = 0; i < reload_n_operands; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_output[i], regno))
	  return 0;

      return (!TEST_HARD_REG_BIT (reload_reg_used_in_op_addr, regno)
	      && !TEST_HARD_REG_BIT (reload_reg_used_in_insn, regno)
	      && !TEST_HARD_REG_BIT (reload_reg_used, regno));

    case RELOAD_FOR_INSN:
      /* These conflict with other outputs with RELOAD_OTHER.  So
	 we need only check for output addresses.  */

      opnum = reload_n_operands;

      /* ... fall through ...  */

    case RELOAD_FOR_OUTPUT:
    case RELOAD_FOR_OUTPUT_ADDRESS:
    case RELOAD_FOR_OUTADDR_ADDRESS:
      /* We already know these can't conflict with a later output.  So the
	 only thing to check are later output addresses.
	 Note that multiple output operands are emitted in reverse order,
	 so the conflicting ones are those with lower indices.  */
      for (i = 0; i < opnum; i++)
	if (TEST_HARD_REG_BIT (reload_reg_used_in_output_addr[i], regno)
	    || TEST_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[i], regno))
	  return 0;

      return 1;

    default:
      gcc_unreachable ();
    }
}