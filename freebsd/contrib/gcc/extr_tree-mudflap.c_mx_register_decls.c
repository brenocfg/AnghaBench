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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  DECL_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STATIC (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TRY_FINALLY_EXPR ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_to_statement_list (scalar_t__,scalar_t__*) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_call_expr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 scalar_t__ convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_stmt (scalar_t__*) ; 
 scalar_t__ mf_decl_eligible_p (scalar_t__) ; 
 int /*<<< orphan*/  mf_mark (scalar_t__) ; 
 int /*<<< orphan*/  mf_marked_p (scalar_t__) ; 
 int /*<<< orphan*/  mf_register_fndecl ; 
 int /*<<< orphan*/  mf_unregister_fndecl ; 
 scalar_t__ mf_varname_tree (scalar_t__) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  size_type_node ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_start (scalar_t__) ; 
 int /*<<< orphan*/  void_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mx_register_decls (tree decl, tree *stmt_list)
{
  tree finally_stmts = NULL_TREE;
  tree_stmt_iterator initially_stmts = tsi_start (*stmt_list);

  while (decl != NULL_TREE)
    {
      if (mf_decl_eligible_p (decl) 
          /* Not already processed.  */
          && ! mf_marked_p (decl)
          /* Automatic variable.  */
          && ! DECL_EXTERNAL (decl)
          && ! TREE_STATIC (decl))
        {
          tree size = NULL_TREE, variable_name;
          tree unregister_fncall, unregister_fncall_params;
          tree register_fncall, register_fncall_params;

	  size = convert (size_type_node, TYPE_SIZE_UNIT (TREE_TYPE (decl)));

          /* (& VARIABLE, sizeof (VARIABLE), __MF_TYPE_STACK) */
          unregister_fncall_params =
            tree_cons (NULL_TREE,
                       convert (ptr_type_node,
                                mf_mark (build1 (ADDR_EXPR,
                                                 build_pointer_type (TREE_TYPE (decl)),
                                                 decl))),
                       tree_cons (NULL_TREE, 
                                  size,
                                  tree_cons (NULL_TREE,
					     /* __MF_TYPE_STACK */
                                             build_int_cst (NULL_TREE, 3),
                                             NULL_TREE)));
          /* __mf_unregister (...) */
          unregister_fncall = build_function_call_expr (mf_unregister_fndecl,
                                                        unregister_fncall_params);

          /* (& VARIABLE, sizeof (VARIABLE), __MF_TYPE_STACK, "name") */
          variable_name = mf_varname_tree (decl);
          register_fncall_params =
            tree_cons (NULL_TREE,
                   convert (ptr_type_node,
                            mf_mark (build1 (ADDR_EXPR,
                                             build_pointer_type (TREE_TYPE (decl)),
                                             decl))),
                       tree_cons (NULL_TREE,
                                  size,
                                  tree_cons (NULL_TREE,
					     /* __MF_TYPE_STACK */
                                             build_int_cst (NULL_TREE, 3),
                                             tree_cons (NULL_TREE,
                                                        variable_name,
                                                        NULL_TREE))));

          /* __mf_register (...) */
          register_fncall = build_function_call_expr (mf_register_fndecl,
                                                      register_fncall_params);

          /* Accumulate the two calls.  */
          /* ??? Set EXPR_LOCATION.  */
          gimplify_stmt (&register_fncall);
          gimplify_stmt (&unregister_fncall);

          /* Add the __mf_register call at the current appending point.  */
          if (tsi_end_p (initially_stmts))
	    warning (0, "mudflap cannot track %qs in stub function",
		     IDENTIFIER_POINTER (DECL_NAME (decl)));
	  else
	    {
	      tsi_link_before (&initially_stmts, register_fncall, TSI_SAME_STMT);

	      /* Accumulate the FINALLY piece.  */
	      append_to_statement_list (unregister_fncall, &finally_stmts);
	    }
          mf_mark (decl);
        }

      decl = TREE_CHAIN (decl);
    }

  /* Actually, (initially_stmts!=NULL) <=> (finally_stmts!=NULL) */
  if (finally_stmts != NULL_TREE)
    {
      tree t = build2 (TRY_FINALLY_EXPR, void_type_node,
                       *stmt_list, finally_stmts);
      *stmt_list = NULL;
      append_to_statement_list (t, stmt_list);
    }
}