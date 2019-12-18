#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_18__ {scalar_t__ next_bb; int /*<<< orphan*/  count; int /*<<< orphan*/  frequency; int /*<<< orphan*/  flags; int /*<<< orphan*/  succs; } ;
struct TYPE_17__ {scalar_t__ dest; int /*<<< orphan*/  count; int /*<<< orphan*/  probability; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_RTL ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EDGE_FALLTHRU ; 
 TYPE_1__* EDGE_SUCC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ENTRY_BLOCK_PTR ; 
 TYPE_2__* EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BR_PROB_BASE ; 
 TYPE_2__* create_basic_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  get_last_insn () ; 
 int /*<<< orphan*/  init_rtl_bb_info (TYPE_2__*) ; 
 int /*<<< orphan*/  label_rtx (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_edge (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  redirect_edge_succ (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tree_block_label (scalar_t__) ; 
 int /*<<< orphan*/  update_bb_for_insn (TYPE_2__*) ; 

__attribute__((used)) static basic_block
construct_init_block (void)
{
  basic_block init_block, first_block;
  edge e = NULL;
  int flags;

  /* Multiple entry points not supported yet.  */
  gcc_assert (EDGE_COUNT (ENTRY_BLOCK_PTR->succs) == 1);
  init_rtl_bb_info (ENTRY_BLOCK_PTR);
  init_rtl_bb_info (EXIT_BLOCK_PTR);
  ENTRY_BLOCK_PTR->flags |= BB_RTL;
  EXIT_BLOCK_PTR->flags |= BB_RTL;

  e = EDGE_SUCC (ENTRY_BLOCK_PTR, 0);

  /* When entry edge points to first basic block, we don't need jump,
     otherwise we have to jump into proper target.  */
  if (e && e->dest != ENTRY_BLOCK_PTR->next_bb)
    {
      tree label = tree_block_label (e->dest);

      emit_jump (label_rtx (label));
      flags = 0;
    }
  else
    flags = EDGE_FALLTHRU;

  init_block = create_basic_block (NEXT_INSN (get_insns ()),
				   get_last_insn (),
				   ENTRY_BLOCK_PTR);
  init_block->frequency = ENTRY_BLOCK_PTR->frequency;
  init_block->count = ENTRY_BLOCK_PTR->count;
  if (e)
    {
      first_block = e->dest;
      redirect_edge_succ (e, init_block);
      e = make_edge (init_block, first_block, flags);
    }
  else
    e = make_edge (init_block, EXIT_BLOCK_PTR, EDGE_FALLTHRU);
  e->probability = REG_BR_PROB_BASE;
  e->count = ENTRY_BLOCK_PTR->count;

  update_bb_for_insn (init_block);
  return init_block;
}