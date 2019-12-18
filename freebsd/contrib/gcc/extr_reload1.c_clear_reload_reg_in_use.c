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
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int when_needed; int opnum; size_t mode; scalar_t__ reg_rtx; } ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
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
 int /*<<< orphan*/  gcc_unreachable () ; 
 unsigned int** hard_regno_nregs ; 
 int n_reloads ; 
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
 TYPE_1__* rld ; 
 unsigned int true_regnum (scalar_t__) ; 

__attribute__((used)) static void
clear_reload_reg_in_use (unsigned int regno, int opnum,
			 enum reload_type type, enum machine_mode mode)
{
  unsigned int nregs = hard_regno_nregs[regno][mode];
  unsigned int start_regno, end_regno, r;
  int i;
  /* A complication is that for some reload types, inheritance might
     allow multiple reloads of the same types to share a reload register.
     We set check_opnum if we have to check only reloads with the same
     operand number, and check_any if we have to check all reloads.  */
  int check_opnum = 0;
  int check_any = 0;
  HARD_REG_SET *used_in_set;

  switch (type)
    {
    case RELOAD_OTHER:
      used_in_set = &reload_reg_used;
      break;

    case RELOAD_FOR_INPUT_ADDRESS:
      used_in_set = &reload_reg_used_in_input_addr[opnum];
      break;

    case RELOAD_FOR_INPADDR_ADDRESS:
      check_opnum = 1;
      used_in_set = &reload_reg_used_in_inpaddr_addr[opnum];
      break;

    case RELOAD_FOR_OUTPUT_ADDRESS:
      used_in_set = &reload_reg_used_in_output_addr[opnum];
      break;

    case RELOAD_FOR_OUTADDR_ADDRESS:
      check_opnum = 1;
      used_in_set = &reload_reg_used_in_outaddr_addr[opnum];
      break;

    case RELOAD_FOR_OPERAND_ADDRESS:
      used_in_set = &reload_reg_used_in_op_addr;
      break;

    case RELOAD_FOR_OPADDR_ADDR:
      check_any = 1;
      used_in_set = &reload_reg_used_in_op_addr_reload;
      break;

    case RELOAD_FOR_OTHER_ADDRESS:
      used_in_set = &reload_reg_used_in_other_addr;
      check_any = 1;
      break;

    case RELOAD_FOR_INPUT:
      used_in_set = &reload_reg_used_in_input[opnum];
      break;

    case RELOAD_FOR_OUTPUT:
      used_in_set = &reload_reg_used_in_output[opnum];
      break;

    case RELOAD_FOR_INSN:
      used_in_set = &reload_reg_used_in_insn;
      break;
    default:
      gcc_unreachable ();
    }
  /* We resolve conflicts with remaining reloads of the same type by
     excluding the intervals of reload registers by them from the
     interval of freed reload registers.  Since we only keep track of
     one set of interval bounds, we might have to exclude somewhat
     more than what would be necessary if we used a HARD_REG_SET here.
     But this should only happen very infrequently, so there should
     be no reason to worry about it.  */

  start_regno = regno;
  end_regno = regno + nregs;
  if (check_opnum || check_any)
    {
      for (i = n_reloads - 1; i >= 0; i--)
	{
	  if (rld[i].when_needed == type
	      && (check_any || rld[i].opnum == opnum)
	      && rld[i].reg_rtx)
	    {
	      unsigned int conflict_start = true_regnum (rld[i].reg_rtx);
	      unsigned int conflict_end
		= (conflict_start
		   + hard_regno_nregs[conflict_start][rld[i].mode]);

	      /* If there is an overlap with the first to-be-freed register,
		 adjust the interval start.  */
	      if (conflict_start <= start_regno && conflict_end > start_regno)
		start_regno = conflict_end;
	      /* Otherwise, if there is a conflict with one of the other
		 to-be-freed registers, adjust the interval end.  */
	      if (conflict_start > start_regno && conflict_start < end_regno)
		end_regno = conflict_start;
	    }
	}
    }

  for (r = start_regno; r < end_regno; r++)
    CLEAR_HARD_REG_BIT (*used_in_set, r);
}