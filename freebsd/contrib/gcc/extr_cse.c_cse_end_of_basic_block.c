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
struct cse_basic_block_data {int path_size; int low_cuid; int high_cuid; int nsets; TYPE_1__* path; scalar_t__ last; } ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ branch; } ;

/* Variables and functions */
 scalar_t__ BARRIER_P (scalar_t__) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ IF_THEN_ELSE ; 
 int INSN_CUID (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ INSN_UID (scalar_t__) ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ JUMP_P (scalar_t__) ; 
 int LABEL_NUSES (scalar_t__) ; 
 scalar_t__ LABEL_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_P (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PARAM_MAX_CSE_PATH_LENGTH ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ PATH_AROUND ; 
 scalar_t__ PATH_NOT_TAKEN ; 
 scalar_t__ PATH_TAKEN ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PUT_MODE (scalar_t__,scalar_t__) ; 
 scalar_t__ QImode ; 
 int /*<<< orphan*/  REG_SETJMP ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ max_uid ; 
 scalar_t__ next_real_insn (scalar_t__) ; 

__attribute__((used)) static void
cse_end_of_basic_block (rtx insn, struct cse_basic_block_data *data,
			int follow_jumps, int skip_blocks)
{
  rtx p = insn, q;
  int nsets = 0;
  int low_cuid = INSN_CUID (insn), high_cuid = INSN_CUID (insn);
  rtx next = INSN_P (insn) ? insn : next_real_insn (insn);
  int path_size = data->path_size;
  int path_entry = 0;
  int i;

  /* Update the previous branch path, if any.  If the last branch was
     previously PATH_TAKEN, mark it PATH_NOT_TAKEN.
     If it was previously PATH_NOT_TAKEN,
     shorten the path by one and look at the previous branch.  We know that
     at least one branch must have been taken if PATH_SIZE is nonzero.  */
  while (path_size > 0)
    {
      if (data->path[path_size - 1].status != PATH_NOT_TAKEN)
	{
	  data->path[path_size - 1].status = PATH_NOT_TAKEN;
	  break;
	}
      else
	path_size--;
    }

  /* If the first instruction is marked with QImode, that means we've
     already processed this block.  Our caller will look at DATA->LAST
     to figure out where to go next.  We want to return the next block
     in the instruction stream, not some branched-to block somewhere
     else.  We accomplish this by pretending our called forbid us to
     follow jumps, or skip blocks.  */
  if (GET_MODE (insn) == QImode)
    follow_jumps = skip_blocks = 0;

  /* Scan to end of this basic block.  */
  while (p && !LABEL_P (p))
    {
      /* Don't cse over a call to setjmp; on some machines (eg VAX)
	 the regs restored by the longjmp come from
	 a later time than the setjmp.  */
      if (PREV_INSN (p) && CALL_P (PREV_INSN (p))
	  && find_reg_note (PREV_INSN (p), REG_SETJMP, NULL))
	break;

      /* A PARALLEL can have lots of SETs in it,
	 especially if it is really an ASM_OPERANDS.  */
      if (INSN_P (p) && GET_CODE (PATTERN (p)) == PARALLEL)
	nsets += XVECLEN (PATTERN (p), 0);
      else if (!NOTE_P (p))
	nsets += 1;

      /* Ignore insns made by CSE; they cannot affect the boundaries of
	 the basic block.  */

      if (INSN_UID (p) <= max_uid && INSN_CUID (p) > high_cuid)
	high_cuid = INSN_CUID (p);
      if (INSN_UID (p) <= max_uid && INSN_CUID (p) < low_cuid)
	low_cuid = INSN_CUID (p);

      /* See if this insn is in our branch path.  If it is and we are to
	 take it, do so.  */
      if (path_entry < path_size && data->path[path_entry].branch == p)
	{
	  if (data->path[path_entry].status != PATH_NOT_TAKEN)
	    p = JUMP_LABEL (p);

	  /* Point to next entry in path, if any.  */
	  path_entry++;
	}

      /* If this is a conditional jump, we can follow it if -fcse-follow-jumps
	 was specified, we haven't reached our maximum path length, there are
	 insns following the target of the jump, this is the only use of the
	 jump label, and the target label is preceded by a BARRIER.

	 Alternatively, we can follow the jump if it branches around a
	 block of code and there are no other branches into the block.
	 In this case invalidate_skipped_block will be called to invalidate any
	 registers set in the block when following the jump.  */

      else if ((follow_jumps || skip_blocks) && path_size < PARAM_VALUE (PARAM_MAX_CSE_PATH_LENGTH) - 1
	       && JUMP_P (p)
	       && GET_CODE (PATTERN (p)) == SET
	       && GET_CODE (SET_SRC (PATTERN (p))) == IF_THEN_ELSE
	       && JUMP_LABEL (p) != 0
	       && LABEL_NUSES (JUMP_LABEL (p)) == 1
	       && NEXT_INSN (JUMP_LABEL (p)) != 0)
	{
	  for (q = PREV_INSN (JUMP_LABEL (p)); q; q = PREV_INSN (q))
	    if ((!NOTE_P (q)
		 || (PREV_INSN (q) && CALL_P (PREV_INSN (q))
		     && find_reg_note (PREV_INSN (q), REG_SETJMP, NULL)))
		&& (!LABEL_P (q) || LABEL_NUSES (q) != 0))
	      break;

	  /* If we ran into a BARRIER, this code is an extension of the
	     basic block when the branch is taken.  */
	  if (follow_jumps && q != 0 && BARRIER_P (q))
	    {
	      /* Don't allow ourself to keep walking around an
		 always-executed loop.  */
	      if (next_real_insn (q) == next)
		{
		  p = NEXT_INSN (p);
		  continue;
		}

	      /* Similarly, don't put a branch in our path more than once.  */
	      for (i = 0; i < path_entry; i++)
		if (data->path[i].branch == p)
		  break;

	      if (i != path_entry)
		break;

	      data->path[path_entry].branch = p;
	      data->path[path_entry++].status = PATH_TAKEN;

	      /* This branch now ends our path.  It was possible that we
		 didn't see this branch the last time around (when the
		 insn in front of the target was a JUMP_INSN that was
		 turned into a no-op).  */
	      path_size = path_entry;

	      p = JUMP_LABEL (p);
	      /* Mark block so we won't scan it again later.  */
	      PUT_MODE (NEXT_INSN (p), QImode);
	    }
	  /* Detect a branch around a block of code.  */
	  else if (skip_blocks && q != 0 && !LABEL_P (q))
	    {
	      rtx tmp;

	      if (next_real_insn (q) == next)
		{
		  p = NEXT_INSN (p);
		  continue;
		}

	      for (i = 0; i < path_entry; i++)
		if (data->path[i].branch == p)
		  break;

	      if (i != path_entry)
		break;

	      /* This is no_labels_between_p (p, q) with an added check for
		 reaching the end of a function (in case Q precedes P).  */
	      for (tmp = NEXT_INSN (p); tmp && tmp != q; tmp = NEXT_INSN (tmp))
		if (LABEL_P (tmp))
		  break;

	      if (tmp == q)
		{
		  data->path[path_entry].branch = p;
		  data->path[path_entry++].status = PATH_AROUND;

		  path_size = path_entry;

		  p = JUMP_LABEL (p);
		  /* Mark block so we won't scan it again later.  */
		  PUT_MODE (NEXT_INSN (p), QImode);
		}
	    }
	}
      p = NEXT_INSN (p);
    }

  data->low_cuid = low_cuid;
  data->high_cuid = high_cuid;
  data->nsets = nsets;
  data->last = p;

  /* If all jumps in the path are not taken, set our path length to zero
     so a rescan won't be done.  */
  for (i = path_size - 1; i >= 0; i--)
    if (data->path[i].status != PATH_NOT_TAKEN)
      break;

  if (i == -1)
    data->path_size = 0;
  else
    data->path_size = path_size;

  /* End the current branch path.  */
  data->path[path_size].branch = 0;
}