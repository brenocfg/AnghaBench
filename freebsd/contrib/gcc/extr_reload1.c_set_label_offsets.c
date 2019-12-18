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
struct elim_table {int /*<<< orphan*/  can_eliminate; int /*<<< orphan*/  initial_offset; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 139 
#define  ADDR_VEC 138 
 int /*<<< orphan*/  BARRIER_P (int /*<<< orphan*/ ) ; 
#define  CALL_INSN 137 
#define  CODE_LABEL 136 
 size_t CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 135 
#define  INSN 134 
#define  JUMP_INSN 133 
#define  LABEL_REF 132 
 int /*<<< orphan*/  LABEL_REF_NONLOCAL_P (int /*<<< orphan*/ ) ; 
 unsigned int NUM_ELIMINABLE_REGS ; 
#define  PARALLEL 131 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
#define  PC 130 
 int /*<<< orphan*/  REG_LABEL ; 
 int /*<<< orphan*/  REG_NOTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_NOTE_KIND (int /*<<< orphan*/ ) ; 
#define  RETURN 129 
#define  SET 128 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
 size_t first_label_num ; 
 int /*<<< orphan*/ ** offsets_at ; 
 int* offsets_known_at ; 
 int /*<<< orphan*/  pc_rtx ; 
 int /*<<< orphan*/  prev_nonnote_insn (int /*<<< orphan*/ ) ; 
 struct elim_table* reg_eliminate ; 
 int /*<<< orphan*/  set_offsets_for_label (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_label_offsets (rtx x, rtx insn, int initial_p)
{
  enum rtx_code code = GET_CODE (x);
  rtx tem;
  unsigned int i;
  struct elim_table *p;

  switch (code)
    {
    case LABEL_REF:
      if (LABEL_REF_NONLOCAL_P (x))
	return;

      x = XEXP (x, 0);

      /* ... fall through ...  */

    case CODE_LABEL:
      /* If we know nothing about this label, set the desired offsets.  Note
	 that this sets the offset at a label to be the offset before a label
	 if we don't know anything about the label.  This is not correct for
	 the label after a BARRIER, but is the best guess we can make.  If
	 we guessed wrong, we will suppress an elimination that might have
	 been possible had we been able to guess correctly.  */

      if (! offsets_known_at[CODE_LABEL_NUMBER (x) - first_label_num])
	{
	  for (i = 0; i < NUM_ELIMINABLE_REGS; i++)
	    offsets_at[CODE_LABEL_NUMBER (x) - first_label_num][i]
	      = (initial_p ? reg_eliminate[i].initial_offset
		 : reg_eliminate[i].offset);
	  offsets_known_at[CODE_LABEL_NUMBER (x) - first_label_num] = 1;
	}

      /* Otherwise, if this is the definition of a label and it is
	 preceded by a BARRIER, set our offsets to the known offset of
	 that label.  */

      else if (x == insn
	       && (tem = prev_nonnote_insn (insn)) != 0
	       && BARRIER_P (tem))
	set_offsets_for_label (insn);
      else
	/* If neither of the above cases is true, compare each offset
	   with those previously recorded and suppress any eliminations
	   where the offsets disagree.  */

	for (i = 0; i < NUM_ELIMINABLE_REGS; i++)
	  if (offsets_at[CODE_LABEL_NUMBER (x) - first_label_num][i]
	      != (initial_p ? reg_eliminate[i].initial_offset
		  : reg_eliminate[i].offset))
	    reg_eliminate[i].can_eliminate = 0;

      return;

    case JUMP_INSN:
      set_label_offsets (PATTERN (insn), insn, initial_p);

      /* ... fall through ...  */

    case INSN:
    case CALL_INSN:
      /* Any labels mentioned in REG_LABEL notes can be branched to indirectly
	 and hence must have all eliminations at their initial offsets.  */
      for (tem = REG_NOTES (x); tem; tem = XEXP (tem, 1))
	if (REG_NOTE_KIND (tem) == REG_LABEL)
	  set_label_offsets (XEXP (tem, 0), insn, 1);
      return;

    case PARALLEL:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      /* Each of the labels in the parallel or address vector must be
	 at their initial offsets.  We want the first field for PARALLEL
	 and ADDR_VEC and the second field for ADDR_DIFF_VEC.  */

      for (i = 0; i < (unsigned) XVECLEN (x, code == ADDR_DIFF_VEC); i++)
	set_label_offsets (XVECEXP (x, code == ADDR_DIFF_VEC, i),
			   insn, initial_p);
      return;

    case SET:
      /* We only care about setting PC.  If the source is not RETURN,
	 IF_THEN_ELSE, or a label, disable any eliminations not at
	 their initial offsets.  Similarly if any arm of the IF_THEN_ELSE
	 isn't one of those possibilities.  For branches to a label,
	 call ourselves recursively.

	 Note that this can disable elimination unnecessarily when we have
	 a non-local goto since it will look like a non-constant jump to
	 someplace in the current function.  This isn't a significant
	 problem since such jumps will normally be when all elimination
	 pairs are back to their initial offsets.  */

      if (SET_DEST (x) != pc_rtx)
	return;

      switch (GET_CODE (SET_SRC (x)))
	{
	case PC:
	case RETURN:
	  return;

	case LABEL_REF:
	  set_label_offsets (SET_SRC (x), insn, initial_p);
	  return;

	case IF_THEN_ELSE:
	  tem = XEXP (SET_SRC (x), 1);
	  if (GET_CODE (tem) == LABEL_REF)
	    set_label_offsets (XEXP (tem, 0), insn, initial_p);
	  else if (GET_CODE (tem) != PC && GET_CODE (tem) != RETURN)
	    break;

	  tem = XEXP (SET_SRC (x), 2);
	  if (GET_CODE (tem) == LABEL_REF)
	    set_label_offsets (XEXP (tem, 0), insn, initial_p);
	  else if (GET_CODE (tem) != PC && GET_CODE (tem) != RETURN)
	    break;
	  return;

	default:
	  break;
	}

      /* If we reach here, all eliminations must be at their initial
	 offset because we are doing a jump to a variable address.  */
      for (p = reg_eliminate; p < &reg_eliminate[NUM_ELIMINABLE_REGS]; p++)
	if (p->offset != p->initial_offset)
	  p->can_eliminate = 0;
      break;

    default:
      break;
    }
}