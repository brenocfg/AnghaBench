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
typedef  enum attr_itanium_class { ____Placeholder_attr_itanium_class } attr_itanium_class ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ASM_INPUT ; 
 scalar_t__ CALL_INSN ; 
 int FALSE ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 size_t INSN_UID (scalar_t__) ; 
 int ITANIUM_CLASS_MMMUL ; 
 int ITANIUM_CLASS_MMSHF ; 
 scalar_t__ LOG_LINKS (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ PROCESSOR_ITANIUM ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ TARGET_EARLY_STOP_BITS ; 
 int TRUE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int* add_cycles ; 
 scalar_t__ asm_noperands (scalar_t__) ; 
 int* clocks ; 
 int /*<<< orphan*/  curr_state ; 
 int /*<<< orphan*/ * dfa_pre_cycle_insn ; 
 int /*<<< orphan*/  dfa_state_size ; 
 int /*<<< orphan*/ * dfa_stop_insn ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,size_t,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int ia64_safe_itanium_class (scalar_t__) ; 
 scalar_t__ ia64_tune ; 
 int /*<<< orphan*/  init_insn_group_barriers () ; 
 scalar_t__ last_scheduled_insn ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prev_cycle_state ; 
 scalar_t__ reload_completed ; 
 scalar_t__ safe_group_barrier_needed (scalar_t__) ; 
 int /*<<< orphan*/  state_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stop_before_p ; 

__attribute__((used)) static int
ia64_dfa_new_cycle (FILE *dump, int verbose, rtx insn, int last_clock,
		    int clock, int *sort_p)
{
  int setup_clocks_p = FALSE;

  gcc_assert (insn && INSN_P (insn));
  if ((reload_completed && safe_group_barrier_needed (insn))
      || (last_scheduled_insn
	  && (GET_CODE (last_scheduled_insn) == CALL_INSN
	      || GET_CODE (PATTERN (last_scheduled_insn)) == ASM_INPUT
	      || asm_noperands (PATTERN (last_scheduled_insn)) >= 0)))
    {
      init_insn_group_barriers ();
      if (verbose && dump)
	fprintf (dump, "//    Stop should be before %d%s\n", INSN_UID (insn),
		 last_clock == clock ? " + cycle advance" : "");
      stop_before_p = 1;
      if (last_clock == clock)
	{
	  state_transition (curr_state, dfa_stop_insn);
	  if (TARGET_EARLY_STOP_BITS)
	    *sort_p = (last_scheduled_insn == NULL_RTX
		       || GET_CODE (last_scheduled_insn) != CALL_INSN);
	  else
	    *sort_p = 0;
	  return 1;
	}
      else if (reload_completed)
	setup_clocks_p = TRUE;
      if (GET_CODE (PATTERN (last_scheduled_insn)) == ASM_INPUT
	  || asm_noperands (PATTERN (last_scheduled_insn)) >= 0)
	state_reset (curr_state);
      else
	{
	  memcpy (curr_state, prev_cycle_state, dfa_state_size);
	  state_transition (curr_state, dfa_stop_insn);
	  state_transition (curr_state, dfa_pre_cycle_insn);
	  state_transition (curr_state, NULL);
	}
    }
  else if (reload_completed)
    setup_clocks_p = TRUE;
  if (setup_clocks_p && ia64_tune == PROCESSOR_ITANIUM
      && GET_CODE (PATTERN (insn)) != ASM_INPUT
      && asm_noperands (PATTERN (insn)) < 0)
    {
      enum attr_itanium_class c = ia64_safe_itanium_class (insn);

      if (c != ITANIUM_CLASS_MMMUL && c != ITANIUM_CLASS_MMSHF)
	{
	  rtx link;
	  int d = -1;

	  for (link = LOG_LINKS (insn); link; link = XEXP (link, 1))
	    if (REG_NOTE_KIND (link) == 0)
	      {
		enum attr_itanium_class dep_class;
		rtx dep_insn = XEXP (link, 0);

		dep_class = ia64_safe_itanium_class (dep_insn);
		if ((dep_class == ITANIUM_CLASS_MMMUL
		     || dep_class == ITANIUM_CLASS_MMSHF)
		    && last_clock - clocks [INSN_UID (dep_insn)] < 4
		    && (d < 0
			|| last_clock - clocks [INSN_UID (dep_insn)] < d))
		  d = last_clock - clocks [INSN_UID (dep_insn)];
	      }
	  if (d >= 0)
	    add_cycles [INSN_UID (insn)] = 3 - d;
	}
    }
  return 0;
}