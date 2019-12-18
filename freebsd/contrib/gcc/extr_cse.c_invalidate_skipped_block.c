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
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  CONST_OR_PURE_CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  invalidate_for_call () ; 
 int /*<<< orphan*/  invalidate_from_clobbers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_memory () ; 
 int /*<<< orphan*/  invalidate_skipped_set ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
invalidate_skipped_block (rtx start)
{
  rtx insn;

  for (insn = start; insn && !LABEL_P (insn);
       insn = NEXT_INSN (insn))
    {
      if (! INSN_P (insn))
	continue;

      if (CALL_P (insn))
	{
	  if (! CONST_OR_PURE_CALL_P (insn))
	    invalidate_memory ();
	  invalidate_for_call ();
	}

      invalidate_from_clobbers (PATTERN (insn));
      note_stores (PATTERN (insn), invalidate_skipped_set, NULL);
    }
}