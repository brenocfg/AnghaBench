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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CODE_LABEL ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int INSN_UID (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE ; 
 scalar_t__ NOTE_INSN_BASIC_BLOCK ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ UNSPECV_INSN_GROUP_BARRIER ; 
 scalar_t__ UNSPEC_VOLATILE ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 int /*<<< orphan*/  emit_insn_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gen_insn_group_barrier (int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ group_barrier_needed (scalar_t__) ; 
 int /*<<< orphan*/  init_insn_group_barriers () ; 

__attribute__((used)) static void
emit_insn_group_barriers (FILE *dump)
{
  rtx insn;
  rtx last_label = 0;
  int insns_since_last_label = 0;

  init_insn_group_barriers ();

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (GET_CODE (insn) == CODE_LABEL)
	{
	  if (insns_since_last_label)
	    last_label = insn;
	  insns_since_last_label = 0;
	}
      else if (GET_CODE (insn) == NOTE
	       && NOTE_LINE_NUMBER (insn) == NOTE_INSN_BASIC_BLOCK)
	{
	  if (insns_since_last_label)
	    last_label = insn;
	  insns_since_last_label = 0;
	}
      else if (GET_CODE (insn) == INSN
	       && GET_CODE (PATTERN (insn)) == UNSPEC_VOLATILE
	       && XINT (PATTERN (insn), 1) == UNSPECV_INSN_GROUP_BARRIER)
	{
	  init_insn_group_barriers ();
	  last_label = 0;
	}
      else if (INSN_P (insn))
	{
	  insns_since_last_label = 1;

	  if (group_barrier_needed (insn))
	    {
	      if (last_label)
		{
		  if (dump)
		    fprintf (dump, "Emitting stop before label %d\n",
			     INSN_UID (last_label));
		  emit_insn_before (gen_insn_group_barrier (GEN_INT (3)), last_label);
		  insn = last_label;

		  init_insn_group_barriers ();
		  last_label = 0;
		}
	    }
	}
    }
}