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
struct propagate_block_info {int flags; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  ASM_OPERANDS 132 
#define  CLOBBER 131 
#define  COND_EXEC 130 
 scalar_t__ COND_EXEC_CODE (scalar_t__) ; 
 scalar_t__ COND_EXEC_TEST (scalar_t__) ; 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
#define  PARALLEL 129 
 int PROP_ASM_SCAN ; 
 scalar_t__ REG_INC ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
#define  SET 128 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  mark_set_1 (struct propagate_block_info*,int,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
mark_set_regs (struct propagate_block_info *pbi, rtx x, rtx insn)
{
  rtx cond = NULL_RTX;
  rtx link;
  enum rtx_code code;
  int flags = pbi->flags;

  if (insn)
    for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
      {
	if (REG_NOTE_KIND (link) == REG_INC)
	  mark_set_1 (pbi, SET, XEXP (link, 0),
		      (GET_CODE (x) == COND_EXEC
		       ? COND_EXEC_TEST (x) : NULL_RTX),
		      insn, flags);
      }
 retry:
  switch (code = GET_CODE (x))
    {
    case SET:
      if (GET_CODE (XEXP (x, 1)) == ASM_OPERANDS)
	flags |= PROP_ASM_SCAN;
      /* Fall through */
    case CLOBBER:
      mark_set_1 (pbi, code, SET_DEST (x), cond, insn, flags);
      return;

    case COND_EXEC:
      cond = COND_EXEC_TEST (x);
      x = COND_EXEC_CODE (x);
      goto retry;

    case PARALLEL:
      {
	int i;

	/* We must scan forwards.  If we have an asm, we need to set
	   the PROP_ASM_SCAN flag before scanning the clobbers.  */
	for (i = 0; i < XVECLEN (x, 0); i++)
	  {
	    rtx sub = XVECEXP (x, 0, i);
	    switch (code = GET_CODE (sub))
	      {
	      case COND_EXEC:
		gcc_assert (!cond);

		cond = COND_EXEC_TEST (sub);
		sub = COND_EXEC_CODE (sub);
		if (GET_CODE (sub) == SET)
		  goto mark_set;
		if (GET_CODE (sub) == CLOBBER)
		  goto mark_clob;
		break;

	      case SET:
	      mark_set:
		if (GET_CODE (XEXP (sub, 1)) == ASM_OPERANDS)
		  flags |= PROP_ASM_SCAN;
		/* Fall through */
	      case CLOBBER:
	      mark_clob:
		mark_set_1 (pbi, code, SET_DEST (sub), cond, insn, flags);
		break;

	      case ASM_OPERANDS:
		flags |= PROP_ASM_SCAN;
		break;

	      default:
		break;
	      }
	  }
	break;
      }

    default:
      break;
    }
}