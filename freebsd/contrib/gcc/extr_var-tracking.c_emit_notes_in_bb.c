#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_20__ {int /*<<< orphan*/  stack_adjust; } ;
typedef  TYPE_3__ dataflow_set ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_18__ {int /*<<< orphan*/  adjust; int /*<<< orphan*/  loc; } ;
struct TYPE_19__ {int type; TYPE_1__ u; int /*<<< orphan*/  insn; } ;
struct TYPE_16__ {int /*<<< orphan*/  vars; } ;
struct TYPE_17__ {int n_mos; TYPE_2__* mos; TYPE_14__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_NOTE_AFTER_INSN ; 
 int /*<<< orphan*/  EMIT_NOTE_BEFORE_INSN ; 
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
#define  MO_ADJUST 134 
#define  MO_CALL 133 
#define  MO_CLOBBER 132 
#define  MO_COPY 131 
#define  MO_SET 130 
#define  MO_USE 129 
#define  MO_USE_NO_VAR 128 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 TYPE_15__* VTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_used_reg_set ; 
 int /*<<< orphan*/  dataflow_set_copy (TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/  dataflow_set_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  dataflow_set_init (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  emit_notes_for_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_mem_delete (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_mem_delete_and_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_mem_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_reg_delete (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_reg_delete_and_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_reg_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_regno_delete (TYPE_3__*,int) ; 

__attribute__((used)) static void
emit_notes_in_bb (basic_block bb)
{
  int i;
  dataflow_set set;

  dataflow_set_init (&set, htab_elements (VTI (bb)->in.vars) + 3);
  dataflow_set_copy (&set, &VTI (bb)->in);

  for (i = 0; i < VTI (bb)->n_mos; i++)
    {
      rtx insn = VTI (bb)->mos[i].insn;

      switch (VTI (bb)->mos[i].type)
	{
	  case MO_CALL:
	    {
	      int r;

	      for (r = 0; r < FIRST_PSEUDO_REGISTER; r++)
		if (TEST_HARD_REG_BIT (call_used_reg_set, r))
		  {
		    var_regno_delete (&set, r);
		  }
	      emit_notes_for_changes (insn, EMIT_NOTE_AFTER_INSN);
	    }
	    break;

	  case MO_USE:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (GET_CODE (loc) == REG)
		var_reg_set (&set, loc);
	      else
		var_mem_set (&set, loc);

	      emit_notes_for_changes (insn, EMIT_NOTE_AFTER_INSN);
	    }
	    break;

	  case MO_SET:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete_and_set (&set, loc, true);
	      else
		var_mem_delete_and_set (&set, loc, true);

	      emit_notes_for_changes (insn, EMIT_NOTE_BEFORE_INSN);
	    }
	    break;

	  case MO_COPY:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete_and_set (&set, loc, false);
	      else
		var_mem_delete_and_set (&set, loc, false);

	      emit_notes_for_changes (insn, EMIT_NOTE_BEFORE_INSN);
	    }
	    break;

	  case MO_USE_NO_VAR:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete (&set, loc, false);
	      else
		var_mem_delete (&set, loc, false);

	      emit_notes_for_changes (insn, EMIT_NOTE_AFTER_INSN);
	    }
	    break;

	  case MO_CLOBBER:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete (&set, loc, true);
	      else
		var_mem_delete (&set, loc, true);

	      emit_notes_for_changes (insn, EMIT_NOTE_BEFORE_INSN);
	    }
	    break;

	  case MO_ADJUST:
	    set.stack_adjust += VTI (bb)->mos[i].u.adjust;
	    break;
	}
    }
  dataflow_set_destroy (&set);
}