#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eh_region {scalar_t__ landing_pad; struct eh_region* outer; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  htab_t ;
struct TYPE_4__ {int uses_eh_lsda; TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  region_array; int /*<<< orphan*/  action_record_data; int /*<<< orphan*/ * region_tree; } ;
typedef  int NOTE_EH_HANDLER ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_INSN_EH_REGION_BEG ; 
 int /*<<< orphan*/  NOTE_INSN_EH_REGION_END ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_EH_REGION ; 
 scalar_t__ SEQUENCE ; 
 scalar_t__ USING_SJLJ_EXCEPTIONS ; 
 int /*<<< orphan*/  VARRAY_UCHAR_INIT (int /*<<< orphan*/ ,int,char*) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action_record_eq ; 
 int /*<<< orphan*/  action_record_hash ; 
 int add_call_site (scalar_t__,int) ; 
 TYPE_2__* cfun ; 
 int collect_one_action_chain (int /*<<< orphan*/ ,struct eh_region*) ; 
 int /*<<< orphan*/  eh_region ; 
 scalar_t__ emit_note_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ emit_note_before (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ flag_non_call_exceptions ; 
 int /*<<< orphan*/  free ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ may_trap_p (int /*<<< orphan*/ ) ; 

unsigned int
convert_to_eh_region_ranges (void)
{
  rtx insn, iter, note;
  htab_t ar_hash;
  int last_action = -3;
  rtx last_action_insn = NULL_RTX;
  rtx last_landing_pad = NULL_RTX;
  rtx first_no_action_insn = NULL_RTX;
  int call_site = 0;

  if (USING_SJLJ_EXCEPTIONS || cfun->eh->region_tree == NULL)
    return 0;

  VARRAY_UCHAR_INIT (cfun->eh->action_record_data, 64, "action_record_data");

  ar_hash = htab_create (31, action_record_hash, action_record_eq, free);

  for (iter = get_insns (); iter ; iter = NEXT_INSN (iter))
    if (INSN_P (iter))
      {
	struct eh_region *region;
	int this_action;
	rtx this_landing_pad;

	insn = iter;
	if (NONJUMP_INSN_P (insn)
	    && GET_CODE (PATTERN (insn)) == SEQUENCE)
	  insn = XVECEXP (PATTERN (insn), 0, 0);

	note = find_reg_note (insn, REG_EH_REGION, NULL_RTX);
	if (!note)
	  {
	    if (! (CALL_P (insn)
		   || (flag_non_call_exceptions
		       && may_trap_p (PATTERN (insn)))))
	      continue;
	    this_action = -1;
	    region = NULL;
	  }
	else
	  {
	    if (INTVAL (XEXP (note, 0)) <= 0)
	      continue;
	    region = VEC_index (eh_region, cfun->eh->region_array, INTVAL (XEXP (note, 0)));
	    this_action = collect_one_action_chain (ar_hash, region);
	  }

	/* Existence of catch handlers, or must-not-throw regions
	   implies that an lsda is needed (even if empty).  */
	if (this_action != -1)
	  cfun->uses_eh_lsda = 1;

	/* Delay creation of region notes for no-action regions
	   until we're sure that an lsda will be required.  */
	else if (last_action == -3)
	  {
	    first_no_action_insn = iter;
	    last_action = -1;
	  }

	/* Cleanups and handlers may share action chains but not
	   landing pads.  Collect the landing pad for this region.  */
	if (this_action >= 0)
	  {
	    struct eh_region *o;
	    for (o = region; ! o->landing_pad ; o = o->outer)
	      continue;
	    this_landing_pad = o->landing_pad;
	  }
	else
	  this_landing_pad = NULL_RTX;

	/* Differing actions or landing pads implies a change in call-site
	   info, which implies some EH_REGION note should be emitted.  */
	if (last_action != this_action
	    || last_landing_pad != this_landing_pad)
	  {
	    /* If we'd not seen a previous action (-3) or the previous
	       action was must-not-throw (-2), then we do not need an
	       end note.  */
	    if (last_action >= -1)
	      {
		/* If we delayed the creation of the begin, do it now.  */
		if (first_no_action_insn)
		  {
		    call_site = add_call_site (NULL_RTX, 0);
		    note = emit_note_before (NOTE_INSN_EH_REGION_BEG,
					     first_no_action_insn);
		    NOTE_EH_HANDLER (note) = call_site;
		    first_no_action_insn = NULL_RTX;
		  }

		note = emit_note_after (NOTE_INSN_EH_REGION_END,
					last_action_insn);
		NOTE_EH_HANDLER (note) = call_site;
	      }

	    /* If the new action is must-not-throw, then no region notes
	       are created.  */
	    if (this_action >= -1)
	      {
		call_site = add_call_site (this_landing_pad,
					   this_action < 0 ? 0 : this_action);
		note = emit_note_before (NOTE_INSN_EH_REGION_BEG, iter);
		NOTE_EH_HANDLER (note) = call_site;
	      }

	    last_action = this_action;
	    last_landing_pad = this_landing_pad;
	  }
	last_action_insn = iter;
      }

  if (last_action >= -1 && ! first_no_action_insn)
    {
      note = emit_note_after (NOTE_INSN_EH_REGION_END, last_action_insn);
      NOTE_EH_HANDLER (note) = call_site;
    }

  htab_delete (ar_hash);
  return 0;
}