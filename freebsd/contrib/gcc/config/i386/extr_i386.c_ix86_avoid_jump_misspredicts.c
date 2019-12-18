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

/* Variables and functions */
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ CALL_INSN ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int INSN_UID (scalar_t__) ; 
 scalar_t__ JUMP_INSN ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  emit_insn_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_align (int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int min_insn_size (scalar_t__) ; 

__attribute__((used)) static void
ix86_avoid_jump_misspredicts (void)
{
  rtx insn, start = get_insns ();
  int nbytes = 0, njumps = 0;
  int isjump = 0;

  /* Look for all minimal intervals of instructions containing 4 jumps.
     The intervals are bounded by START and INSN.  NBYTES is the total
     size of instructions in the interval including INSN and not including
     START.  When the NBYTES is smaller than 16 bytes, it is possible
     that the end of START and INSN ends up in the same 16byte page.

     The smallest offset in the page INSN can start is the case where START
     ends on the offset 0.  Offset of INSN is then NBYTES - sizeof (INSN).
     We add p2align to 16byte window with maxskip 17 - NBYTES + sizeof (INSN).
     */
  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {

      nbytes += min_insn_size (insn);
      if (dump_file)
        fprintf(dump_file, "Insn %i estimated to %i bytes\n",
		INSN_UID (insn), min_insn_size (insn));
      if ((GET_CODE (insn) == JUMP_INSN
	   && GET_CODE (PATTERN (insn)) != ADDR_VEC
	   && GET_CODE (PATTERN (insn)) != ADDR_DIFF_VEC)
	  || GET_CODE (insn) == CALL_INSN)
	njumps++;
      else
	continue;

      while (njumps > 3)
	{
	  start = NEXT_INSN (start);
	  if ((GET_CODE (start) == JUMP_INSN
	       && GET_CODE (PATTERN (start)) != ADDR_VEC
	       && GET_CODE (PATTERN (start)) != ADDR_DIFF_VEC)
	      || GET_CODE (start) == CALL_INSN)
	    njumps--, isjump = 1;
	  else
	    isjump = 0;
	  nbytes -= min_insn_size (start);
	}
      gcc_assert (njumps >= 0);
      if (dump_file)
        fprintf (dump_file, "Interval %i to %i has %i bytes\n",
		INSN_UID (start), INSN_UID (insn), nbytes);

      if (njumps == 3 && isjump && nbytes < 16)
	{
	  int padsize = 15 - nbytes + min_insn_size (insn);

	  if (dump_file)
	    fprintf (dump_file, "Padding insn %i by %i bytes!\n",
		     INSN_UID (insn), padsize);
          emit_insn_before (gen_align (GEN_INT (padsize)), insn);
	}
    }
}