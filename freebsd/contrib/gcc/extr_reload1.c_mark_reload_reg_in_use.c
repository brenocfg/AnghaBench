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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

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
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int** hard_regno_nregs ; 
 int /*<<< orphan*/  reload_reg_used ; 
 int /*<<< orphan*/  reload_reg_used_at_all ; 
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

__attribute__((used)) static void
mark_reload_reg_in_use (unsigned int regno, int opnum, enum reload_type type,
			enum machine_mode mode)
{
  unsigned int nregs = hard_regno_nregs[regno][mode];
  unsigned int i;

  for (i = regno; i < nregs + regno; i++)
    {
      switch (type)
	{
	case RELOAD_OTHER:
	  SET_HARD_REG_BIT (reload_reg_used, i);
	  break;

	case RELOAD_FOR_INPUT_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_input_addr[opnum], i);
	  break;

	case RELOAD_FOR_INPADDR_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_inpaddr_addr[opnum], i);
	  break;

	case RELOAD_FOR_OUTPUT_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_output_addr[opnum], i);
	  break;

	case RELOAD_FOR_OUTADDR_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_outaddr_addr[opnum], i);
	  break;

	case RELOAD_FOR_OPERAND_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_op_addr, i);
	  break;

	case RELOAD_FOR_OPADDR_ADDR:
	  SET_HARD_REG_BIT (reload_reg_used_in_op_addr_reload, i);
	  break;

	case RELOAD_FOR_OTHER_ADDRESS:
	  SET_HARD_REG_BIT (reload_reg_used_in_other_addr, i);
	  break;

	case RELOAD_FOR_INPUT:
	  SET_HARD_REG_BIT (reload_reg_used_in_input[opnum], i);
	  break;

	case RELOAD_FOR_OUTPUT:
	  SET_HARD_REG_BIT (reload_reg_used_in_output[opnum], i);
	  break;

	case RELOAD_FOR_INSN:
	  SET_HARD_REG_BIT (reload_reg_used_in_insn, i);
	  break;
	}

      SET_HARD_REG_BIT (reload_reg_used_at_all, i);
    }
}