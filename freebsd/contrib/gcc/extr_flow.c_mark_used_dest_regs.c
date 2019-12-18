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

/* Variables and functions */
 int ARG_POINTER_REGNUM ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ EXPR_LIST ; 
 int FRAME_POINTER_REGNUM ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int PROP_AUTOINC ; 
 int PROP_REG_INFO ; 
 int REGNO (scalar_t__) ; 
 int REG_BYTES (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ ZERO_EXTRACT ; 
 int /*<<< orphan*/  find_auto_inc (struct propagate_block_info*,scalar_t__,scalar_t__) ; 
 scalar_t__* fixed_regs ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  mark_used_regs (struct propagate_block_info*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  record_subregs_of_mode (scalar_t__) ; 
 int /*<<< orphan*/  reload_completed ; 

__attribute__((used)) static bool
mark_used_dest_regs (struct propagate_block_info *pbi, rtx x, rtx cond, rtx insn)
{
  int regno;
  bool mark_dest = false;
  rtx dest = x;
  
  /* On some platforms calls return values spread over several 
     locations.  These locations are wrapped in a EXPR_LIST rtx
     together with a CONST_INT offset.  */
  if (GET_CODE (x) == EXPR_LIST
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    x = XEXP (x, 0);
  
  if (x == NULL_RTX)
    return false;

  /* If storing into MEM, don't show it as being used.  But do
     show the address as being used.  */
  if (MEM_P (x))
    {
#ifdef AUTO_INC_DEC
      if (pbi->flags & PROP_AUTOINC)
	find_auto_inc (pbi, x, insn);
#endif
      mark_used_regs (pbi, XEXP (x, 0), cond, insn);
      return true;
    }
	    
  /* Storing in STRICT_LOW_PART is like storing in a reg
     in that this SET might be dead, so ignore it in TESTREG.
     but in some other ways it is like using the reg.
     
     Storing in a SUBREG or a bit field is like storing the entire
     register in that if the register's value is not used
	       then this SET is not needed.  */
  while (GET_CODE (x) == STRICT_LOW_PART
	 || GET_CODE (x) == ZERO_EXTRACT
	 || GET_CODE (x) == SUBREG)
    {
#ifdef CANNOT_CHANGE_MODE_CLASS
      if ((pbi->flags & PROP_REG_INFO) && GET_CODE (x) == SUBREG)
	record_subregs_of_mode (x);
#endif
      
      /* Modifying a single register in an alternate mode
	 does not use any of the old value.  But these other
	 ways of storing in a register do use the old value.  */
      if (GET_CODE (x) == SUBREG
	  && !((REG_BYTES (SUBREG_REG (x))
		+ UNITS_PER_WORD - 1) / UNITS_PER_WORD
	       > (REG_BYTES (x)
		  + UNITS_PER_WORD - 1) / UNITS_PER_WORD))
	;
      else
	mark_dest = true;
      
      x = XEXP (x, 0);
    }
  
  /* If this is a store into a register or group of registers,
     recursively scan the value being stored.  */
  if (REG_P (x)
      && (regno = REGNO (x),
	  !(regno == FRAME_POINTER_REGNUM
	    && (!reload_completed || frame_pointer_needed)))
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
      && !(regno == HARD_FRAME_POINTER_REGNUM
	   && (!reload_completed || frame_pointer_needed))
#endif
#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM
      && !(regno == ARG_POINTER_REGNUM && fixed_regs[regno])
#endif
      )
    {
      if (mark_dest)
	mark_used_regs (pbi, dest, cond, insn);
      return true;
    }
  return false;
}