#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elt_loc_list {scalar_t__ loc; int /*<<< orphan*/  setting_insn; scalar_t__ in_libcall; struct elt_loc_list* next; } ;
typedef  scalar_t__ rtx ;
struct TYPE_3__ {struct elt_loc_list* locs; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int INSN_UID (scalar_t__) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_EQUIV ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int adjust_libcall_notes (scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ asm_noperands (int /*<<< orphan*/ ) ; 
 scalar_t__ constprop_register (scalar_t__,scalar_t__,scalar_t__,int) ; 
 TYPE_1__* cselib_lookup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dump_file ; 
 scalar_t__ find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gcse_constant_p (scalar_t__) ; 
 int /*<<< orphan*/  local_const_prop_count ; 
 int /*<<< orphan*/  local_copy_prop_count ; 
 int /*<<< orphan*/  print_rtl (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ try_replace_reg (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
do_local_cprop (rtx x, rtx insn, bool alter_jumps, rtx *libcall_sp)
{
  rtx newreg = NULL, newcnst = NULL;

  /* Rule out USE instructions and ASM statements as we don't want to
     change the hard registers mentioned.  */
  if (REG_P (x)
      && (REGNO (x) >= FIRST_PSEUDO_REGISTER
          || (GET_CODE (PATTERN (insn)) != USE
	      && asm_noperands (PATTERN (insn)) < 0)))
    {
      cselib_val *val = cselib_lookup (x, GET_MODE (x), 0);
      struct elt_loc_list *l;

      if (!val)
	return false;
      for (l = val->locs; l; l = l->next)
	{
	  rtx this_rtx = l->loc;
	  rtx note;

	  /* Don't CSE non-constant values out of libcall blocks.  */
	  if (l->in_libcall && ! CONSTANT_P (this_rtx))
	    continue;

	  if (gcse_constant_p (this_rtx))
	    newcnst = this_rtx;
	  if (REG_P (this_rtx) && REGNO (this_rtx) >= FIRST_PSEUDO_REGISTER
	      /* Don't copy propagate if it has attached REG_EQUIV note.
		 At this point this only function parameters should have
		 REG_EQUIV notes and if the argument slot is used somewhere
		 explicitly, it means address of parameter has been taken,
		 so we should not extend the lifetime of the pseudo.  */
	      && (!(note = find_reg_note (l->setting_insn, REG_EQUIV, NULL_RTX))
		  || ! MEM_P (XEXP (note, 0))))
	    newreg = this_rtx;
	}
      if (newcnst && constprop_register (insn, x, newcnst, alter_jumps))
	{
	  /* If we find a case where we can't fix the retval REG_EQUAL notes
	     match the new register, we either have to abandon this replacement
	     or fix delete_trivially_dead_insns to preserve the setting insn,
	     or make it delete the REG_EUAQL note, and fix up all passes that
	     require the REG_EQUAL note there.  */
	  bool adjusted;

	  adjusted = adjust_libcall_notes (x, newcnst, insn, libcall_sp);
	  gcc_assert (adjusted);
	  
	  if (dump_file != NULL)
	    {
	      fprintf (dump_file, "LOCAL CONST-PROP: Replacing reg %d in ",
		       REGNO (x));
	      fprintf (dump_file, "insn %d with constant ",
		       INSN_UID (insn));
	      print_rtl (dump_file, newcnst);
	      fprintf (dump_file, "\n");
	    }
	  local_const_prop_count++;
	  return true;
	}
      else if (newreg && newreg != x && try_replace_reg (x, newreg, insn))
	{
	  adjust_libcall_notes (x, newreg, insn, libcall_sp);
	  if (dump_file != NULL)
	    {
	      fprintf (dump_file,
		       "LOCAL COPY-PROP: Replacing reg %d in insn %d",
		       REGNO (x), INSN_UID (insn));
	      fprintf (dump_file, " with reg %d\n", REGNO (newreg));
	    }
	  local_copy_prop_count++;
	  return true;
	}
    }
  return false;
}