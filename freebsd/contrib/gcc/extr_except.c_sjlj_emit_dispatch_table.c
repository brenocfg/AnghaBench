#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sjlj_lp_info {int /*<<< orphan*/  dispatch_index; int /*<<< orphan*/  directly_reachable; } ;
struct eh_region {int /*<<< orphan*/  post_landing_pad; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_2__* edge ;
typedef  TYPE_3__* basic_block ;
struct TYPE_11__ {TYPE_1__* eh; } ;
struct TYPE_10__ {int /*<<< orphan*/  count; int /*<<< orphan*/  next_bb; } ;
struct TYPE_9__ {int /*<<< orphan*/  probability; int /*<<< orphan*/  count; } ;
struct TYPE_8__ {int last_region_number; int /*<<< orphan*/  region_array; int /*<<< orphan*/  filter; int /*<<< orphan*/  exc_ptr; int /*<<< orphan*/  sjlj_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_BR_PROB_BASE ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_7__* cfun ; 
 int /*<<< orphan*/  convert_memory_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_mode (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* emit_to_new_bb_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  expand_builtin_setjmp_receiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  integer_type_node ; 
 TYPE_2__* make_edge (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ptr_mode ; 
 scalar_t__ sjlj_fc_call_site_ofs ; 
 scalar_t__ sjlj_fc_data_ofs ; 
 int /*<<< orphan*/  start_sequence () ; 
 scalar_t__ word_mode ; 

__attribute__((used)) static void
sjlj_emit_dispatch_table (rtx dispatch_label, struct sjlj_lp_info *lp_info)
{
  int i, first_reachable;
  rtx mem, dispatch, seq, fc;
  rtx before;
  basic_block bb;
  edge e;

  fc = cfun->eh->sjlj_fc;

  start_sequence ();

  emit_label (dispatch_label);

#ifndef DONT_USE_BUILTIN_SETJMP
  expand_builtin_setjmp_receiver (dispatch_label);
#endif

  /* Load up dispatch index, exc_ptr and filter values from the
     function context.  */
  mem = adjust_address (fc, TYPE_MODE (integer_type_node),
			sjlj_fc_call_site_ofs);
  dispatch = copy_to_reg (mem);

  mem = adjust_address (fc, word_mode, sjlj_fc_data_ofs);
  if (word_mode != ptr_mode)
    {
#ifdef POINTERS_EXTEND_UNSIGNED
      mem = convert_memory_address (ptr_mode, mem);
#else
      mem = convert_to_mode (ptr_mode, mem, 0);
#endif
    }
  emit_move_insn (cfun->eh->exc_ptr, mem);

  mem = adjust_address (fc, word_mode, sjlj_fc_data_ofs + UNITS_PER_WORD);
  emit_move_insn (cfun->eh->filter, mem);

  /* Jump to one of the directly reachable regions.  */
  /* ??? This really ought to be using a switch statement.  */

  first_reachable = 0;
  for (i = cfun->eh->last_region_number; i > 0; --i)
    {
      if (! lp_info[i].directly_reachable)
	continue;

      if (! first_reachable)
	{
	  first_reachable = i;
	  continue;
	}

      emit_cmp_and_jump_insns (dispatch, GEN_INT (lp_info[i].dispatch_index),
			       EQ, NULL_RTX, TYPE_MODE (integer_type_node), 0,
	                       ((struct eh_region *)VEC_index (eh_region, cfun->eh->region_array, i))
				->post_landing_pad);
    }

  seq = get_insns ();
  end_sequence ();

  before = (((struct eh_region *)VEC_index (eh_region, cfun->eh->region_array, first_reachable))
	    ->post_landing_pad);

  bb = emit_to_new_bb_before (seq, before);
  e = make_edge (bb, bb->next_bb, EDGE_FALLTHRU);
  e->count = bb->count;
  e->probability = REG_BR_PROB_BASE;
}