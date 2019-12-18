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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int first_save_gpr; int last_save_gpr; int first_restore_gpr; int last_restore_gpr; } ;

/* Variables and functions */
 int BASE_REGNUM ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ INSN ; 
 int /*<<< orphan*/  INSN_ADDRESSES_NEW (scalar_t__,int) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ MEM ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ REG ; 
 int REGNO (scalar_t__) ; 
 int RETURN_REGNUM ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int STACK_POINTER_REGNUM ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ cfun_frame_layout ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ eliminate_constant_term (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ emit_insn_before (scalar_t__,scalar_t__) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ load_multiple_operation (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_insn (scalar_t__) ; 
 scalar_t__ restore_gprs (scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  s390_update_frame_layout () ; 
 scalar_t__ save_gprs (scalar_t__,int,int,int) ; 
 scalar_t__ store_multiple_operation (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s390_optimize_prologue (void)
{
  rtx insn, new_insn, next_insn;

  /* Do a final recompute of the frame-related data.  */

  s390_update_frame_layout ();

  /* If all special registers are in fact used, there's nothing we
     can do, so no point in walking the insn list.  */

  if (cfun_frame_layout.first_save_gpr <= BASE_REGNUM 
      && cfun_frame_layout.last_save_gpr >= BASE_REGNUM
      && (TARGET_CPU_ZARCH 
          || (cfun_frame_layout.first_save_gpr <= RETURN_REGNUM 
              && cfun_frame_layout.last_save_gpr >= RETURN_REGNUM)))
    return;

  /* Search for prologue/epilogue insns and replace them.  */

  for (insn = get_insns (); insn; insn = next_insn)
    {
      int first, last, off;
      rtx set, base, offset;

      next_insn = NEXT_INSN (insn);

      if (GET_CODE (insn) != INSN)
	continue;

      if (GET_CODE (PATTERN (insn)) == PARALLEL
	  && store_multiple_operation (PATTERN (insn), VOIDmode))
	{
	  set = XVECEXP (PATTERN (insn), 0, 0);
	  first = REGNO (SET_SRC (set));
	  last = first + XVECLEN (PATTERN (insn), 0) - 1;
	  offset = const0_rtx;
	  base = eliminate_constant_term (XEXP (SET_DEST (set), 0), &offset);
	  off = INTVAL (offset);

	  if (GET_CODE (base) != REG || off < 0)
	    continue;
	  if (cfun_frame_layout.first_save_gpr != -1
	      && (cfun_frame_layout.first_save_gpr < first
		  || cfun_frame_layout.last_save_gpr > last))
	    continue;
	  if (REGNO (base) != STACK_POINTER_REGNUM
	      && REGNO (base) != HARD_FRAME_POINTER_REGNUM)
	    continue;
	  if (first > BASE_REGNUM || last < BASE_REGNUM)
	    continue;

	  if (cfun_frame_layout.first_save_gpr != -1)
	    {
	      new_insn 	= save_gprs (base, 
				     off + (cfun_frame_layout.first_save_gpr
					    - first) * UNITS_PER_WORD, 
				     cfun_frame_layout.first_save_gpr,
				     cfun_frame_layout.last_save_gpr);
	      new_insn = emit_insn_before (new_insn, insn);
	      INSN_ADDRESSES_NEW (new_insn, -1);
	    }

	  remove_insn (insn);
	  continue;
	}

      if (cfun_frame_layout.first_save_gpr == -1
	  && GET_CODE (PATTERN (insn)) == SET
	  && GET_CODE (SET_SRC (PATTERN (insn))) == REG
	  && (REGNO (SET_SRC (PATTERN (insn))) == BASE_REGNUM
	      || (!TARGET_CPU_ZARCH
		  && REGNO (SET_SRC (PATTERN (insn))) == RETURN_REGNUM))
	  && GET_CODE (SET_DEST (PATTERN (insn))) == MEM)
	{
	  set = PATTERN (insn);
	  first = REGNO (SET_SRC (set));
	  offset = const0_rtx;
	  base = eliminate_constant_term (XEXP (SET_DEST (set), 0), &offset);
	  off = INTVAL (offset);

	  if (GET_CODE (base) != REG || off < 0)
	    continue;
	  if (REGNO (base) != STACK_POINTER_REGNUM
	      && REGNO (base) != HARD_FRAME_POINTER_REGNUM)
	    continue;

	  remove_insn (insn);
	  continue;
	}

      if (GET_CODE (PATTERN (insn)) == PARALLEL
	  && load_multiple_operation (PATTERN (insn), VOIDmode))
	{
	  set = XVECEXP (PATTERN (insn), 0, 0);
	  first = REGNO (SET_DEST (set));
	  last = first + XVECLEN (PATTERN (insn), 0) - 1;
	  offset = const0_rtx;
	  base = eliminate_constant_term (XEXP (SET_SRC (set), 0), &offset);
	  off = INTVAL (offset);

	  if (GET_CODE (base) != REG || off < 0)
	    continue;
	  if (cfun_frame_layout.first_restore_gpr != -1
	      && (cfun_frame_layout.first_restore_gpr < first
		  || cfun_frame_layout.last_restore_gpr > last))
	    continue;
	  if (REGNO (base) != STACK_POINTER_REGNUM
	      && REGNO (base) != HARD_FRAME_POINTER_REGNUM)
	    continue;
	  if (first > BASE_REGNUM || last < BASE_REGNUM)
	    continue;

	  if (cfun_frame_layout.first_restore_gpr != -1)
	    {
	      new_insn = restore_gprs (base, 
				       off + (cfun_frame_layout.first_restore_gpr
					      - first) * UNITS_PER_WORD, 
				       cfun_frame_layout.first_restore_gpr,
				       cfun_frame_layout.last_restore_gpr);
	      new_insn = emit_insn_before (new_insn, insn);
	      INSN_ADDRESSES_NEW (new_insn, -1);
	    }

	  remove_insn (insn);
	  continue;
	}

      if (cfun_frame_layout.first_restore_gpr == -1
	  && GET_CODE (PATTERN (insn)) == SET
	  && GET_CODE (SET_DEST (PATTERN (insn))) == REG
	  && (REGNO (SET_DEST (PATTERN (insn))) == BASE_REGNUM
	      || (!TARGET_CPU_ZARCH
		  && REGNO (SET_DEST (PATTERN (insn))) == RETURN_REGNUM))
	  && GET_CODE (SET_SRC (PATTERN (insn))) == MEM)
	{
	  set = PATTERN (insn);
	  first = REGNO (SET_DEST (set));
	  offset = const0_rtx;
	  base = eliminate_constant_term (XEXP (SET_SRC (set), 0), &offset);
	  off = INTVAL (offset);

	  if (GET_CODE (base) != REG || off < 0)
	    continue;
	  if (REGNO (base) != STACK_POINTER_REGNUM
	      && REGNO (base) != HARD_FRAME_POINTER_REGNUM)
	    continue;

	  remove_insn (insn);
	  continue;
	}
    }
}