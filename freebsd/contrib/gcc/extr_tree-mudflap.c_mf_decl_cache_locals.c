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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_commit_edge_inserts () ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gimplify_to_stmt_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_edge_copies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_cache_mask_decl ; 
 int /*<<< orphan*/  mf_cache_mask_decl_l ; 
 int /*<<< orphan*/  mf_cache_shift_decl ; 
 int /*<<< orphan*/  mf_cache_shift_decl_l ; 
 int /*<<< orphan*/  mf_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mf_decl_cache_locals (void)
{
  tree t, shift_init_stmts, mask_init_stmts;
  tree_stmt_iterator tsi;

  /* Build the cache vars.  */
  mf_cache_shift_decl_l
    = mf_mark (create_tmp_var (TREE_TYPE (mf_cache_shift_decl),
                               "__mf_lookup_shift_l"));

  mf_cache_mask_decl_l
    = mf_mark (create_tmp_var (TREE_TYPE (mf_cache_mask_decl),
                               "__mf_lookup_mask_l"));

  /* Build initialization nodes for the cache vars.  We just load the
     globals into the cache variables.  */
  t = build2 (MODIFY_EXPR, TREE_TYPE (mf_cache_shift_decl_l),
              mf_cache_shift_decl_l, mf_cache_shift_decl);
  SET_EXPR_LOCATION (t, DECL_SOURCE_LOCATION (current_function_decl));
  gimplify_to_stmt_list (&t);
  shift_init_stmts = t;

  t = build2 (MODIFY_EXPR, TREE_TYPE (mf_cache_mask_decl_l),
              mf_cache_mask_decl_l, mf_cache_mask_decl);
  SET_EXPR_LOCATION (t, DECL_SOURCE_LOCATION (current_function_decl));
  gimplify_to_stmt_list (&t);
  mask_init_stmts = t;

  /* Anticipating multiple entry points, we insert the cache vars
     initializers in each successor of the ENTRY_BLOCK_PTR.  */
  for (tsi = tsi_start (shift_init_stmts);
       ! tsi_end_p (tsi);
       tsi_next (&tsi))
    insert_edge_copies (tsi_stmt (tsi), ENTRY_BLOCK_PTR);

  for (tsi = tsi_start (mask_init_stmts);
       ! tsi_end_p (tsi);
       tsi_next (&tsi))
    insert_edge_copies (tsi_stmt (tsi), ENTRY_BLOCK_PTR);
  bsi_commit_edge_inserts ();
}