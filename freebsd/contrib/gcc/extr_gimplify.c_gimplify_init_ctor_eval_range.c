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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REF ; 
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ CONSTRUCTOR ; 
 int /*<<< orphan*/  CONSTRUCTOR_ELTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_artificial_label () ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_init_ctor_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
gimplify_init_ctor_eval_range (tree object, tree lower, tree upper,
			       tree value, tree array_elt_type,
			       tree *pre_p, bool cleared)
{
  tree loop_entry_label, loop_exit_label;
  tree var, var_type, cref;

  loop_entry_label = create_artificial_label ();
  loop_exit_label = create_artificial_label ();

  /* Create and initialize the index variable.  */
  var_type = TREE_TYPE (upper);
  var = create_tmp_var (var_type, NULL);
  append_to_statement_list (build2 (MODIFY_EXPR, var_type, var, lower), pre_p);

  /* Add the loop entry label.  */
  append_to_statement_list (build1 (LABEL_EXPR,
				    void_type_node,
				    loop_entry_label),
			    pre_p);

  /* Build the reference.  */
  cref = build4 (ARRAY_REF, array_elt_type, unshare_expr (object),
		 var, NULL_TREE, NULL_TREE);

  /* If we are a constructor, just call gimplify_init_ctor_eval to do
     the store.  Otherwise just assign value to the reference.  */

  if (TREE_CODE (value) == CONSTRUCTOR)
    /* NB we might have to call ourself recursively through
       gimplify_init_ctor_eval if the value is a constructor.  */
    gimplify_init_ctor_eval (cref, CONSTRUCTOR_ELTS (value),
			     pre_p, cleared);
  else
    append_to_statement_list (build2 (MODIFY_EXPR, TREE_TYPE (cref),
				      cref, value),
			      pre_p);

  /* We exit the loop when the index var is equal to the upper bound.  */
  gimplify_and_add (build3 (COND_EXPR, void_type_node,
			    build2 (EQ_EXPR, boolean_type_node,
				    var, upper),
			    build1 (GOTO_EXPR,
				    void_type_node,
				    loop_exit_label),
			    NULL_TREE),
		    pre_p);

  /* Otherwise, increment the index var...  */
  append_to_statement_list (build2 (MODIFY_EXPR, var_type, var,
				    build2 (PLUS_EXPR, var_type, var,
					    fold_convert (var_type,
							  integer_one_node))),
			    pre_p);

  /* ...and jump back to the loop entry.  */
  append_to_statement_list (build1 (GOTO_EXPR,
				    void_type_node,
				    loop_entry_label),
			    pre_p);

  /* Add the loop exit label.  */
  append_to_statement_list (build1 (LABEL_EXPR,
				    void_type_node,
				    loop_exit_label),
			    pre_p);
}