#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_23__ {int /*<<< orphan*/  count; } ;
struct TYPE_22__ {int /*<<< orphan*/  probability; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; TYPE_2__* dest; TYPE_2__* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  ARRAY_REF ; 
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  BSI_CONTINUE_LINKING ; 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  GT_EXPR ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  LT_EXPR ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUTH_OR_EXPR ; 
 int /*<<< orphan*/  TSI_CONTINUE_LINKING ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 TYPE_2__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_2__*) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_2__*) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* create_empty_bb (TYPE_2__*) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dom_info_available_p (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_edge (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ flag_mudflap_threads ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_to_stmt_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  make_edge (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_single_succ_edge (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_cache_array_decl ; 
 int /*<<< orphan*/  mf_cache_mask_decl ; 
 int /*<<< orphan*/  mf_cache_mask_decl_l ; 
 int /*<<< orphan*/  mf_cache_shift_decl ; 
 int /*<<< orphan*/  mf_cache_shift_decl_l ; 
 int /*<<< orphan*/  mf_cache_struct_type ; 
 int /*<<< orphan*/  mf_cache_structptr_type ; 
 int /*<<< orphan*/  mf_check_fndecl ; 
 int /*<<< orphan*/  mf_file_function_line_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_uintptr_type ; 
 int /*<<< orphan*/  set_immediate_dominator (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* split_block (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* split_block_after_labels (TYPE_2__*) ; 
 int /*<<< orphan*/  tree_block_label (TYPE_2__*) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
mf_build_check_statement_for (tree base, tree limit,
                              block_stmt_iterator *instr_bsi,
                              location_t *locus, tree dirflag)
{
  tree_stmt_iterator head, tsi;
  block_stmt_iterator bsi;
  basic_block cond_bb, then_bb, join_bb;
  edge e;
  tree cond, t, u, v;
  tree mf_base;
  tree mf_elem;
  tree mf_limit;

  /* We first need to split the current basic block, and start altering
     the CFG.  This allows us to insert the statements we're about to
     construct into the right basic blocks.  */

  cond_bb = bb_for_stmt (bsi_stmt (*instr_bsi));
  bsi = *instr_bsi;
  bsi_prev (&bsi);
  if (! bsi_end_p (bsi))
    e = split_block (cond_bb, bsi_stmt (bsi));
  else
    e = split_block_after_labels (cond_bb);
  cond_bb = e->src;
  join_bb = e->dest;

  /* A recap at this point: join_bb is the basic block at whose head
     is the gimple statement for which this check expression is being
     built.  cond_bb is the (possibly new, synthetic) basic block the
     end of which will contain the cache-lookup code, and a
     conditional that jumps to the cache-miss code or, much more
     likely, over to join_bb.  */

  /* Create the bb that contains the cache-miss fallback block (mf_check).  */
  then_bb = create_empty_bb (cond_bb);
  make_edge (cond_bb, then_bb, EDGE_TRUE_VALUE);
  make_single_succ_edge (then_bb, join_bb, EDGE_FALLTHRU);

  /* Mark the pseudo-fallthrough edge from cond_bb to join_bb.  */
  e = find_edge (cond_bb, join_bb);
  e->flags = EDGE_FALSE_VALUE;
  e->count = cond_bb->count;
  e->probability = REG_BR_PROB_BASE;

  /* Update dominance info.  Note that bb_join's data was
     updated by split_block.  */
  if (dom_info_available_p (CDI_DOMINATORS))
    {
      set_immediate_dominator (CDI_DOMINATORS, then_bb, cond_bb);
      set_immediate_dominator (CDI_DOMINATORS, join_bb, cond_bb);
    }

  /* Build our local variables.  */
  mf_elem = create_tmp_var (mf_cache_structptr_type, "__mf_elem");
  mf_base = create_tmp_var (mf_uintptr_type, "__mf_base");
  mf_limit = create_tmp_var (mf_uintptr_type, "__mf_limit");

  /* Build: __mf_base = (uintptr_t) <base address expression>.  */
  t = build2 (MODIFY_EXPR, void_type_node, mf_base,
              convert (mf_uintptr_type, unshare_expr (base)));
  SET_EXPR_LOCUS (t, locus);
  gimplify_to_stmt_list (&t);
  head = tsi_start (t);
  tsi = tsi_last (t);

  /* Build: __mf_limit = (uintptr_t) <limit address expression>.  */
  t = build2 (MODIFY_EXPR, void_type_node, mf_limit,
              convert (mf_uintptr_type, unshare_expr (limit)));
  SET_EXPR_LOCUS (t, locus);
  gimplify_to_stmt_list (&t);
  tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);

  /* Build: __mf_elem = &__mf_lookup_cache [(__mf_base >> __mf_shift)
                                            & __mf_mask].  */
  t = build2 (RSHIFT_EXPR, mf_uintptr_type, mf_base,
              (flag_mudflap_threads ? mf_cache_shift_decl : mf_cache_shift_decl_l));
  t = build2 (BIT_AND_EXPR, mf_uintptr_type, t,
              (flag_mudflap_threads ? mf_cache_mask_decl : mf_cache_mask_decl_l));
  t = build4 (ARRAY_REF,
              TREE_TYPE (TREE_TYPE (mf_cache_array_decl)),
              mf_cache_array_decl, t, NULL_TREE, NULL_TREE);
  t = build1 (ADDR_EXPR, mf_cache_structptr_type, t);
  t = build2 (MODIFY_EXPR, void_type_node, mf_elem, t);
  SET_EXPR_LOCUS (t, locus);
  gimplify_to_stmt_list (&t);
  tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);

  /* Quick validity check.

     if (__mf_elem->low > __mf_base
         || (__mf_elem_high < __mf_limit))
        {
          __mf_check ();
          ... and only if single-threaded:
          __mf_lookup_shift_1 = f...;
          __mf_lookup_mask_l = ...;
        }

     It is expected that this body of code is rarely executed so we mark
     the edge to the THEN clause of the conditional jump as unlikely.  */

  /* Construct t <-- '__mf_elem->low  > __mf_base'.  */
  t = build3 (COMPONENT_REF, mf_uintptr_type,
              build1 (INDIRECT_REF, mf_cache_struct_type, mf_elem),
              TYPE_FIELDS (mf_cache_struct_type), NULL_TREE);
  t = build2 (GT_EXPR, boolean_type_node, t, mf_base);

  /* Construct '__mf_elem->high < __mf_limit'.

     First build:
        1) u <--  '__mf_elem->high'
        2) v <--  '__mf_limit'.

     Then build 'u <-- (u < v).  */

  u = build3 (COMPONENT_REF, mf_uintptr_type,
              build1 (INDIRECT_REF, mf_cache_struct_type, mf_elem),
              TREE_CHAIN (TYPE_FIELDS (mf_cache_struct_type)), NULL_TREE);

  v = mf_limit;

  u = build2 (LT_EXPR, boolean_type_node, u, v);

  /* Build the composed conditional: t <-- 't || u'.  Then store the
     result of the evaluation of 't' in a temporary variable which we
     can use as the condition for the conditional jump.  */
  t = build2 (TRUTH_OR_EXPR, boolean_type_node, t, u);
  cond = create_tmp_var (boolean_type_node, "__mf_unlikely_cond");
  t = build2 (MODIFY_EXPR, boolean_type_node, cond, t);
  gimplify_to_stmt_list (&t);
  tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);

  /* Build the conditional jump.  'cond' is just a temporary so we can
     simply build a void COND_EXPR.  We do need labels in both arms though.  */
  t = build3 (COND_EXPR, void_type_node, cond,
              build1 (GOTO_EXPR, void_type_node, tree_block_label (then_bb)),
              build1 (GOTO_EXPR, void_type_node, tree_block_label (join_bb)));
  SET_EXPR_LOCUS (t, locus);
  tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);

  /* At this point, after so much hard work, we have only constructed
     the conditional jump,

     if (__mf_elem->low > __mf_base
         || (__mf_elem_high < __mf_limit))

     The lowered GIMPLE tree representing this code is in the statement
     list starting at 'head'.

     We can insert this now in the current basic block, i.e. the one that
     the statement we're instrumenting was originally in.  */
  bsi = bsi_last (cond_bb);
  for (tsi = head; ! tsi_end_p (tsi); tsi_next (&tsi))
    bsi_insert_after (&bsi, tsi_stmt (tsi), BSI_CONTINUE_LINKING);

  /*  Now build up the body of the cache-miss handling:

     __mf_check();
     refresh *_l vars.

     This is the body of the conditional.  */
  
  u = tree_cons (NULL_TREE,
                 mf_file_function_line_tree (locus == NULL ? UNKNOWN_LOCATION
                                             : *locus),
                 NULL_TREE);
  u = tree_cons (NULL_TREE, dirflag, u);
  /* NB: we pass the overall [base..limit] range to mf_check.  */
  u = tree_cons (NULL_TREE, 
                 fold_build2 (PLUS_EXPR, integer_type_node,
			      fold_build2 (MINUS_EXPR, mf_uintptr_type, mf_limit, mf_base),
			      integer_one_node),
                 u);
  u = tree_cons (NULL_TREE, mf_base, u);
  t = build_function_call_expr (mf_check_fndecl, u);
  gimplify_to_stmt_list (&t);
  head = tsi_start (t);
  tsi = tsi_last (t);

  if (! flag_mudflap_threads)
    {
      t = build2 (MODIFY_EXPR, void_type_node,
                  mf_cache_shift_decl_l, mf_cache_shift_decl);
      tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);

      t = build2 (MODIFY_EXPR, void_type_node,
                  mf_cache_mask_decl_l, mf_cache_mask_decl);
      tsi_link_after (&tsi, t, TSI_CONTINUE_LINKING);
    }

  /* Insert the check code in the THEN block.  */
  bsi = bsi_start (then_bb);
  for (tsi = head; ! tsi_end_p (tsi); tsi_next (&tsi))
    bsi_insert_after (&bsi, tsi_stmt (tsi), BSI_CONTINUE_LINKING);

  *instr_bsi = bsi_start (join_bb);
  bsi_next (instr_bsi);
}