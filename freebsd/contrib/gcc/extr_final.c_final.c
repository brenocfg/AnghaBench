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
typedef  scalar_t__ LABEL_REFS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CC_STATUS_INIT ; 
 int INSN_ADDRESSES (int) ; 
 unsigned int INSN_ADDRESSES_SIZE () ; 
 int INSN_UID (scalar_t__) ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 int LABEL_NUSES (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ NOTE_SOURCE_FILE (scalar_t__) ; 
 scalar_t__ NOTE_SOURCE_LOCATION (scalar_t__) ; 
 scalar_t__ SDB_DEBUG ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 scalar_t__ final_scan_insn (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  init_recog () ; 
 int insn_current_address ; 
 scalar_t__ last_ignored_compare ; 
 scalar_t__ write_symbols ; 

void
final (rtx first, FILE *file, int optimize)
{
  rtx insn;
  int max_uid = 0;
  int seen = 0;

  last_ignored_compare = 0;

#ifdef SDB_DEBUGGING_INFO
  /* When producing SDB debugging info, delete troublesome line number
     notes from inlined functions in other files as well as duplicate
     line number notes.  */
  if (write_symbols == SDB_DEBUG)
    {
      rtx last = 0;
      for (insn = first; insn; insn = NEXT_INSN (insn))
	if (NOTE_P (insn) && NOTE_LINE_NUMBER (insn) > 0)
	  {
	    if (last != 0
#ifdef USE_MAPPED_LOCATION
		&& NOTE_SOURCE_LOCATION (insn) == NOTE_SOURCE_LOCATION (last)
#else
		&& NOTE_LINE_NUMBER (insn) == NOTE_LINE_NUMBER (last)
		&& NOTE_SOURCE_FILE (insn) == NOTE_SOURCE_FILE (last)
#endif
	      )
	      {
		delete_insn (insn);	/* Use delete_note.  */
		continue;
	      }
	    last = insn;
	  }
    }
#endif

  for (insn = first; insn; insn = NEXT_INSN (insn))
    {
      if (INSN_UID (insn) > max_uid)       /* Find largest UID.  */
	max_uid = INSN_UID (insn);
#ifdef HAVE_cc0
      /* If CC tracking across branches is enabled, record the insn which
	 jumps to each branch only reached from one place.  */
      if (optimize && JUMP_P (insn))
	{
	  rtx lab = JUMP_LABEL (insn);
	  if (lab && LABEL_NUSES (lab) == 1)
	    {
	      LABEL_REFS (lab) = insn;
	    }
	}
#endif
    }

  init_recog ();

  CC_STATUS_INIT;

  /* Output the insns.  */
  for (insn = NEXT_INSN (first); insn;)
    {
#ifdef HAVE_ATTR_length
      if ((unsigned) INSN_UID (insn) >= INSN_ADDRESSES_SIZE ())
	{
	  /* This can be triggered by bugs elsewhere in the compiler if
	     new insns are created after init_insn_lengths is called.  */
	  gcc_assert (NOTE_P (insn));
	  insn_current_address = -1;
	}
      else
	insn_current_address = INSN_ADDRESSES (INSN_UID (insn));
#endif /* HAVE_ATTR_length */

      insn = final_scan_insn (insn, file, optimize, 0, &seen);
    }
}