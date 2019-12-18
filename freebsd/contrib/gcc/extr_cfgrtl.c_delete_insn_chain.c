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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_delete_note_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_insn (int /*<<< orphan*/ ) ; 

void
delete_insn_chain (rtx start, rtx finish)
{
  rtx next;

  /* Unchain the insns one by one.  It would be quicker to delete all of these
     with a single unchaining, rather than one at a time, but we need to keep
     the NOTE's.  */
  while (1)
    {
      next = NEXT_INSN (start);
      if (NOTE_P (start) && !can_delete_note_p (start))
	;
      else
	next = delete_insn (start);

      if (start == finish)
	break;
      start = next;
    }
}