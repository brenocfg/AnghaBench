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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int CONST_INT ; 
 scalar_t__ DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (scalar_t__) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
#define  MEM 129 
 int /*<<< orphan*/  PUT_MODE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Pmode ; 
#define  REG 128 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SImode ; 
 int SYMBOL_REF ; 
 scalar_t__ TARGET_128BIT_LONG_DOUBLE ; 
 scalar_t__ TARGET_64BIT ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XFmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_address (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_constant (int /*<<< orphan*/ ) ; 
 int ix86_split_to_parts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ offsettable_memref_p (int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 scalar_t__ push_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
ix86_split_long_move (rtx operands[])
{
  rtx part[2][3];
  int nparts;
  int push = 0;
  int collisions = 0;
  enum machine_mode mode = GET_MODE (operands[0]);

  /* The DFmode expanders may ask us to move double.
     For 64bit target this is single move.  By hiding the fact
     here we simplify i386.md splitters.  */
  if (GET_MODE_SIZE (GET_MODE (operands[0])) == 8 && TARGET_64BIT)
    {
      /* Optimize constant pool reference to immediates.  This is used by
	 fp moves, that force all constants to memory to allow combining.  */

      if (GET_CODE (operands[1]) == MEM
	  && GET_CODE (XEXP (operands[1], 0)) == SYMBOL_REF
	  && CONSTANT_POOL_ADDRESS_P (XEXP (operands[1], 0)))
	operands[1] = get_pool_constant (XEXP (operands[1], 0));
      if (push_operand (operands[0], VOIDmode))
	{
	  operands[0] = copy_rtx (operands[0]);
	  PUT_MODE (operands[0], Pmode);
	}
      else
        operands[0] = gen_lowpart (DImode, operands[0]);
      operands[1] = gen_lowpart (DImode, operands[1]);
      emit_move_insn (operands[0], operands[1]);
      return;
    }

  /* The only non-offsettable memory we handle is push.  */
  if (push_operand (operands[0], VOIDmode))
    push = 1;
  else
    gcc_assert (GET_CODE (operands[0]) != MEM
		|| offsettable_memref_p (operands[0]));

  nparts = ix86_split_to_parts (operands[1], part[1], GET_MODE (operands[0]));
  ix86_split_to_parts (operands[0], part[0], GET_MODE (operands[0]));

  /* When emitting push, take care for source operands on the stack.  */
  if (push && GET_CODE (operands[1]) == MEM
      && reg_overlap_mentioned_p (stack_pointer_rtx, operands[1]))
    {
      if (nparts == 3)
	part[1][1] = change_address (part[1][1], GET_MODE (part[1][1]),
				     XEXP (part[1][2], 0));
      part[1][0] = change_address (part[1][0], GET_MODE (part[1][0]),
				   XEXP (part[1][1], 0));
    }

  /* We need to do copy in the right order in case an address register
     of the source overlaps the destination.  */
  if (REG_P (part[0][0]) && GET_CODE (part[1][0]) == MEM)
    {
      if (reg_overlap_mentioned_p (part[0][0], XEXP (part[1][0], 0)))
	collisions++;
      if (reg_overlap_mentioned_p (part[0][1], XEXP (part[1][0], 0)))
	collisions++;
      if (nparts == 3
	  && reg_overlap_mentioned_p (part[0][2], XEXP (part[1][0], 0)))
	collisions++;

      /* Collision in the middle part can be handled by reordering.  */
      if (collisions == 1 && nparts == 3
	  && reg_overlap_mentioned_p (part[0][1], XEXP (part[1][0], 0)))
	{
	  rtx tmp;
	  tmp = part[0][1]; part[0][1] = part[0][2]; part[0][2] = tmp;
	  tmp = part[1][1]; part[1][1] = part[1][2]; part[1][2] = tmp;
	}

      /* If there are more collisions, we can't handle it by reordering.
	 Do an lea to the last part and use only one colliding move.  */
      else if (collisions > 1)
	{
	  rtx base;

	  collisions = 1;

	  base = part[0][nparts - 1];

	  /* Handle the case when the last part isn't valid for lea.
	     Happens in 64-bit mode storing the 12-byte XFmode.  */
	  if (GET_MODE (base) != Pmode)
	    base = gen_rtx_REG (Pmode, REGNO (base));

	  emit_insn (gen_rtx_SET (VOIDmode, base, XEXP (part[1][0], 0)));
	  part[1][0] = replace_equiv_address (part[1][0], base);
	  part[1][1] = replace_equiv_address (part[1][1],
				      plus_constant (base, UNITS_PER_WORD));
	  if (nparts == 3)
	    part[1][2] = replace_equiv_address (part[1][2],
				      plus_constant (base, 8));
	}
    }

  if (push)
    {
      if (!TARGET_64BIT)
	{
	  if (nparts == 3)
	    {
	      if (TARGET_128BIT_LONG_DOUBLE && mode == XFmode)
                emit_insn (gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, GEN_INT (-4)));
	      emit_move_insn (part[0][2], part[1][2]);
	    }
	}
      else
	{
	  /* In 64bit mode we don't have 32bit push available.  In case this is
	     register, it is OK - we will just use larger counterpart.  We also
	     retype memory - these comes from attempt to avoid REX prefix on
	     moving of second half of TFmode value.  */
	  if (GET_MODE (part[1][1]) == SImode)
	    {
	      switch (GET_CODE (part[1][1]))
		{
		case MEM:
		  part[1][1] = adjust_address (part[1][1], DImode, 0);
		  break;

		case REG:
		  part[1][1] = gen_rtx_REG (DImode, REGNO (part[1][1]));
		  break;

		default:
		  gcc_unreachable ();
		}

	      if (GET_MODE (part[1][0]) == SImode)
		part[1][0] = part[1][1];
	    }
	}
      emit_move_insn (part[0][1], part[1][1]);
      emit_move_insn (part[0][0], part[1][0]);
      return;
    }

  /* Choose correct order to not overwrite the source before it is copied.  */
  if ((REG_P (part[0][0])
       && REG_P (part[1][1])
       && (REGNO (part[0][0]) == REGNO (part[1][1])
	   || (nparts == 3
	       && REGNO (part[0][0]) == REGNO (part[1][2]))))
      || (collisions > 0
	  && reg_overlap_mentioned_p (part[0][0], XEXP (part[1][0], 0))))
    {
      if (nparts == 3)
	{
	  operands[2] = part[0][2];
	  operands[3] = part[0][1];
	  operands[4] = part[0][0];
	  operands[5] = part[1][2];
	  operands[6] = part[1][1];
	  operands[7] = part[1][0];
	}
      else
	{
	  operands[2] = part[0][1];
	  operands[3] = part[0][0];
	  operands[5] = part[1][1];
	  operands[6] = part[1][0];
	}
    }
  else
    {
      if (nparts == 3)
	{
	  operands[2] = part[0][0];
	  operands[3] = part[0][1];
	  operands[4] = part[0][2];
	  operands[5] = part[1][0];
	  operands[6] = part[1][1];
	  operands[7] = part[1][2];
	}
      else
	{
	  operands[2] = part[0][0];
	  operands[3] = part[0][1];
	  operands[5] = part[1][0];
	  operands[6] = part[1][1];
	}
    }

  /* If optimizing for size, attempt to locally unCSE nonzero constants.  */
  if (optimize_size)
    {
      if (GET_CODE (operands[5]) == CONST_INT
	  && operands[5] != const0_rtx
	  && REG_P (operands[2]))
	{
	  if (GET_CODE (operands[6]) == CONST_INT
	      && INTVAL (operands[6]) == INTVAL (operands[5]))
	    operands[6] = operands[2];

	  if (nparts == 3
	      && GET_CODE (operands[7]) == CONST_INT
	      && INTVAL (operands[7]) == INTVAL (operands[5]))
	    operands[7] = operands[2];
	}

      if (nparts == 3
	  && GET_CODE (operands[6]) == CONST_INT
	  && operands[6] != const0_rtx
	  && REG_P (operands[3])
	  && GET_CODE (operands[7]) == CONST_INT
	  && INTVAL (operands[7]) == INTVAL (operands[6]))
	operands[7] = operands[3];
    }

  emit_move_insn (operands[2], operands[5]);
  emit_move_insn (operands[3], operands[6]);
  if (nparts == 3)
    emit_move_insn (operands[4], operands[7]);

  return;
}