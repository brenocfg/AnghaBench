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
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;
typedef  int /*<<< orphan*/  INSN_LOCATOR ;

/* Variables and functions */
 scalar_t__ BLOCK_FOR_INSN (int /*<<< orphan*/ *) ; 
 int DECL_SOURCE_LINE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEXT_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ NOTE_INSN_FUNCTION_BEG ; 
 scalar_t__ NOTE_LINE_NUMBER (int /*<<< orphan*/ *) ; 
 scalar_t__ NOTE_P (int /*<<< orphan*/ *) ; 
 int XINT (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_insns () ; 
 int insn_line (int /*<<< orphan*/ *) ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  prologue_locator ; 
 int /*<<< orphan*/  remove_insn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rtx
find_block_prologue_insns (void)
{
  rtx first_prologue_insn = NULL;
  rtx last_prologue_insn = NULL;
  rtx line_number_note = NULL;
  rtx tmp_insn;
  int num_prologue_insns = 0;
  int total_insns = 0;
  int prologue_line = DECL_SOURCE_LINE (cfun->decl) - 1;
  bool other_insns_before_prologue = false;
  bool start_of_fnbody_found = false;

  /* Go through all the insns and find the first prologue insn, the
     last prologue insn, the source line location note, and whether or
     not there are any "real" insns that occur before the first
     prologue insn.  Re-set the insn locator for prologue insns to the
     prologue locator.  */

  for (tmp_insn = get_insns(); tmp_insn; tmp_insn = NEXT_INSN (tmp_insn))
    {
      if (INSN_P (tmp_insn))
	{
	  if (insn_line (tmp_insn) == prologue_line)
	    {
	      if (!first_prologue_insn)
		first_prologue_insn = tmp_insn;
	      num_prologue_insns++;
	      last_prologue_insn = tmp_insn;
	      INSN_LOCATOR (tmp_insn) = prologue_locator;
	    }
	  else if (!first_prologue_insn
		   && start_of_fnbody_found)
	    other_insns_before_prologue = true;
	}
      else if (NOTE_P (tmp_insn)
	       && NOTE_LINE_NUMBER (tmp_insn) == NOTE_INSN_FUNCTION_BEG)
	start_of_fnbody_found = true;
      else if (NOTE_P (tmp_insn)
	       && (XINT (tmp_insn, 5) == prologue_line))
	line_number_note = tmp_insn;
    }

  /* If there were no prologue insns, return now.  */

  if (!first_prologue_insn)
    return NULL;

  /* If the source location note for the line before the beginning of the
     function was found, remove it.  */

  if (line_number_note)
    remove_insn (line_number_note);

  /* If other real insns got moved above the prologue insns, we can't
     pull out the prologue insns, so return now.  */

  if (other_insns_before_prologue && (optimize > 0))
    return NULL;

  /* Count the number of insns between the first prologue insn and the
     last prologue insn; also count the number of non-prologue insns
     between the first prologue insn and the last prologue insn.  */

  tmp_insn = first_prologue_insn;
  while (tmp_insn != last_prologue_insn)
    {
      total_insns++;
      tmp_insn = NEXT_INSN (tmp_insn);
    }
  total_insns++;

  /* If more than half of the insns between the first & last prologue
     insns are not prologue insns, then there is too much code that
     got moved in between prologue insns (by optimizations), so we
     will not try to pull it out.  */
  
  if ((num_prologue_insns * 2) <= total_insns)
    return NULL;

  /* Make sure all the prologue insns are within one basic block.
     If the insns cross a basic block boundary, then there is a chance
     that moving them will cause incorrect code, so don't do it.  */

  gcc_assert (first_prologue_insn != NULL);
  gcc_assert (last_prologue_insn != NULL);

  if (BLOCK_FOR_INSN (first_prologue_insn) != 
      BLOCK_FOR_INSN (last_prologue_insn))
    return NULL;

  return last_prologue_insn;
}