#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ x_start; scalar_t__ y_start; int ninsns; int local_count; int /*<<< orphan*/  input_valid; } ;
struct TYPE_5__ {scalar_t__ x_start; scalar_t__ ninsns; } ;
struct equiv_info {int mode; int need_rerun; int check_input_conflict; int had_input_conflict; int dying_inputs; TYPE_1__ cur; int /*<<< orphan*/ * x_local; int /*<<< orphan*/ * y_local; int /*<<< orphan*/  y_local_live; int /*<<< orphan*/  x_local_live; int /*<<< orphan*/  input_reg; int /*<<< orphan*/  y_input; int /*<<< orphan*/  x_input; TYPE_2__ best_match; int /*<<< orphan*/  y_block; int /*<<< orphan*/  x_block; scalar_t__ y_end; scalar_t__ x_end; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  regset_head ;

/* Variables and functions */
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BB_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_REG_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_REG_SET (int /*<<< orphan*/ *) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int STRUCT_EQUIV_FINAL ; 
 int STRUCT_EQUIV_MATCH_JUMPS ; 
 int STRUCT_EQUIV_NEED_FULL_BLOCK ; 
 int STRUCT_EQUIV_START ; 
 scalar_t__ any_condjump_p (scalar_t__) ; 
 scalar_t__ assign_reg_reg_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bitmap_intersect_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  condjump_equiv_p (struct equiv_info*,int) ; 
 int /*<<< orphan*/  find_dying_inputs (struct equiv_info*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  insns_match_p (scalar_t__,scalar_t__,struct equiv_info*) ; 
 scalar_t__ onlyjump_p (scalar_t__) ; 
 int /*<<< orphan*/  resolve_input_conflict (struct equiv_info*) ; 
 scalar_t__ returnjump_p (scalar_t__) ; 
 int /*<<< orphan*/  side_effects_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplejump_p (scalar_t__) ; 
 int /*<<< orphan*/  struct_equiv_improve_checkpoint (TYPE_2__*,struct equiv_info*) ; 
 int /*<<< orphan*/  struct_equiv_init (int,struct equiv_info*) ; 
 int /*<<< orphan*/  struct_equiv_merge (scalar_t__,scalar_t__,struct equiv_info*) ; 
 int /*<<< orphan*/  struct_equiv_restore_checkpoint (TYPE_2__*,struct equiv_info*) ; 

int
struct_equiv_block_eq (int mode, struct equiv_info *info)
{
  rtx x_stop, y_stop;
  rtx xi, yi;
  int i;

  if (mode & STRUCT_EQUIV_START)
    {
      x_stop = BB_HEAD (info->x_block);
      y_stop = BB_HEAD (info->y_block);
      if (!x_stop || !y_stop)
	return 0;
    }
  else
    {
      x_stop = info->cur.x_start;
      y_stop = info->cur.y_start;
    }
  if (!struct_equiv_init (mode, info))
    gcc_unreachable ();

  /* Skip simple jumps at the end of the blocks.  Complex jumps still
     need to be compared for equivalence, which we'll do below.  */

  xi = BB_END (info->x_block);
  if (onlyjump_p (xi)
      || (returnjump_p (xi) && !side_effects_p (PATTERN (xi))))
    {
      info->cur.x_start = xi;
      xi = PREV_INSN (xi);
    }

  yi = BB_END (info->y_block);
  if (onlyjump_p (yi)
      || (returnjump_p (yi) && !side_effects_p (PATTERN (yi))))
    {
      info->cur.y_start = yi;
      /* Count everything except for unconditional jump as insn.  */
      /* ??? Is it right to count unconditional jumps with a clobber?
	 Should we count conditional returns?  */
      if (!simplejump_p (yi) && !returnjump_p (yi) && info->cur.x_start)
	info->cur.ninsns++;
      yi = PREV_INSN (yi);
    }

  if (mode & STRUCT_EQUIV_MATCH_JUMPS)
    {
      /* The caller is expected to have compared the jumps already, but we
	 need to match them again to get any local registers and inputs.  */
      gcc_assert (!info->cur.x_start == !info->cur.y_start);
      if (info->cur.x_start)
	{
	  if (any_condjump_p (info->cur.x_start)
	      ? !condjump_equiv_p (info, false)
	      : !insns_match_p (info->cur.x_start, info->cur.y_start, info))
	    gcc_unreachable ();
	}
      else if (any_condjump_p (xi) && any_condjump_p (yi))
	{
	  info->cur.x_start = xi;
	  info->cur.y_start = yi;
	  xi = PREV_INSN (xi);
	  yi = PREV_INSN (yi);
	  info->cur.ninsns++;
	  if (!condjump_equiv_p (info, false))
	    gcc_unreachable ();
	}
      if (info->cur.x_start && info->mode & STRUCT_EQUIV_FINAL)
	struct_equiv_merge (info->cur.x_start, info->cur.y_start, info);
    }

  struct_equiv_improve_checkpoint (&info->best_match, info);
  info->x_end = xi;
  info->y_end = yi;
  if (info->cur.x_start != x_stop)
    for (;;)
      {
	/* Ignore notes.  */
	while (!INSN_P (xi) && xi != x_stop)
	  xi = PREV_INSN (xi);

	while (!INSN_P (yi) && yi != y_stop)
	  yi = PREV_INSN (yi);

	if (!insns_match_p (xi, yi, info))
	  break;
	if (INSN_P (xi))
	  {
	    if (info->mode & STRUCT_EQUIV_FINAL)
	      struct_equiv_merge (xi, yi, info);
	    info->cur.ninsns++;
	    struct_equiv_improve_checkpoint (&info->best_match, info);
	  }
	if (xi == x_stop || yi == y_stop)
	  {
	    /* If we reached the start of at least one of the blocks, but
	       best_match hasn't been advanced back to the first valid insn
	       yet, represent the increased benefit of completing the block
	       as an increased instruction count.  */
	    if (info->best_match.x_start != info->cur.x_start
		&& (xi == BB_HEAD (info->x_block)
		    || yi == BB_HEAD (info->y_block)))
	      {
		info->cur.ninsns++;
		struct_equiv_improve_checkpoint (&info->best_match, info);
		info->cur.ninsns--;
		if (info->best_match.ninsns > info->cur.ninsns)
		  info->best_match.ninsns = info->cur.ninsns;
	      }
	    break;
	  }
	xi = PREV_INSN (xi);
	yi = PREV_INSN (yi);
      }

  /* If we failed to match an insn, but had some changes registered from
     trying to make the insns match, we need to cancel these changes now.  */
  cancel_changes (0);
  /* Restore to best_match to get the sequence with the best known-so-far
     cost-benefit difference.  */
  struct_equiv_restore_checkpoint (&info->best_match, info);

  /* Include preceding notes and labels in the cross-jump / if-conversion.
     One, this may bring us to the head of the blocks.
     Two, it keeps line number notes as matched as may be.  */
  if (info->cur.ninsns)
    {
      xi = info->cur.x_start;
      yi = info->cur.y_start;
      while (xi != x_stop && !INSN_P (PREV_INSN (xi)))
	xi = PREV_INSN (xi);

      while (yi != y_stop && !INSN_P (PREV_INSN (yi)))
	yi = PREV_INSN (yi);

      info->cur.x_start = xi;
      info->cur.y_start = yi;
    }

  if (!info->cur.input_valid)
    info->x_input = info->y_input = info->input_reg = NULL_RTX;
  if (!info->need_rerun)
    {
      find_dying_inputs (info);
      if (info->mode & STRUCT_EQUIV_FINAL)
	{
	  if (info->check_input_conflict && ! resolve_input_conflict (info))
	    gcc_unreachable ();
	}
      else
	{
	  bool input_conflict = info->had_input_conflict;

	  if (!input_conflict
	      && info->dying_inputs > 1
	      && bitmap_intersect_p (info->x_local_live, info->y_local_live))
	    {
	      regset_head clobbered_regs;

	      INIT_REG_SET (&clobbered_regs);
	      for (i = 0; i < info->cur.local_count; i++)
		{
		  if (assign_reg_reg_set (&clobbered_regs, info->y_local[i], 0))
		    {
		      input_conflict = true;
		      break;
		    }
		  assign_reg_reg_set (&clobbered_regs, info->x_local[i], 1);
		}
	      CLEAR_REG_SET (&clobbered_regs);
	    }
	  if (input_conflict && !info->check_input_conflict)
	    info->need_rerun = true;
	  info->check_input_conflict = input_conflict;
	}
    }

  if (info->mode & STRUCT_EQUIV_NEED_FULL_BLOCK
      && (info->cur.x_start != x_stop || info->cur.y_start != y_stop))
    return 0;
  return info->cur.ninsns;
}