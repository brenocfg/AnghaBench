#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_21__ {int /*<<< orphan*/  stack_adjust; int /*<<< orphan*/  vars; } ;
typedef  TYPE_3__ dataflow_set ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_19__ {int /*<<< orphan*/  adjust; int /*<<< orphan*/  loc; } ;
struct TYPE_20__ {int type; TYPE_1__ u; } ;
struct TYPE_18__ {int n_mos; TYPE_2__* mos; TYPE_3__ out; TYPE_3__ in; } ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
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
 TYPE_17__* VTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_used_reg_set ; 
 int /*<<< orphan*/  dataflow_set_copy (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dataflow_set_destroy (TYPE_3__*) ; 
 int dataflow_set_different (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dataflow_set_init (TYPE_3__*,scalar_t__) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_mem_delete (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_mem_delete_and_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_mem_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_reg_delete (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_reg_delete_and_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_reg_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_regno_delete (TYPE_3__*,int) ; 

__attribute__((used)) static bool
compute_bb_dataflow (basic_block bb)
{
  int i, n, r;
  bool changed;
  dataflow_set old_out;
  dataflow_set *in = &VTI (bb)->in;
  dataflow_set *out = &VTI (bb)->out;

  dataflow_set_init (&old_out, htab_elements (VTI (bb)->out.vars) + 3);
  dataflow_set_copy (&old_out, out);
  dataflow_set_copy (out, in);

  n = VTI (bb)->n_mos;
  for (i = 0; i < n; i++)
    {
      switch (VTI (bb)->mos[i].type)
	{
	  case MO_CALL:
	    for (r = 0; r < FIRST_PSEUDO_REGISTER; r++)
	      if (TEST_HARD_REG_BIT (call_used_reg_set, r))
		var_regno_delete (out, r);
	    break;

	  case MO_USE:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (GET_CODE (loc) == REG)
		var_reg_set (out, loc);
	      else if (GET_CODE (loc) == MEM)
		var_mem_set (out, loc);
	    }
	    break;

	  case MO_SET:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete_and_set (out, loc, true);
	      else if (MEM_P (loc))
		var_mem_delete_and_set (out, loc, true);
	    }
	    break;

	  case MO_COPY:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete_and_set (out, loc, false);
	      else if (MEM_P (loc))
		var_mem_delete_and_set (out, loc, false);
	    }
	    break;

	  case MO_USE_NO_VAR:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete (out, loc, false);
	      else if (MEM_P (loc))
		var_mem_delete (out, loc, false);
	    }
	    break;

	  case MO_CLOBBER:
	    {
	      rtx loc = VTI (bb)->mos[i].u.loc;

	      if (REG_P (loc))
		var_reg_delete (out, loc, true);
	      else if (MEM_P (loc))
		var_mem_delete (out, loc, true);
	    }
	    break;

	  case MO_ADJUST:
	    out->stack_adjust += VTI (bb)->mos[i].u.adjust;
	    break;
	}
    }

  changed = dataflow_set_different (&old_out, out);
  dataflow_set_destroy (&old_out);
  return changed;
}