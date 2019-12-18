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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (scalar_t__) ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ CP_TYPE_CONST_P (scalar_t__) ; 
 int /*<<< orphan*/  INIT_EXPR ; 
 int LOOKUP_DESTRUCTOR ; 
 int LOOKUP_NONVIRTUAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Weffc__ ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_aggr_init (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_class_member_access_expr (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ build_default_init (scalar_t__,scalar_t__) ; 
 scalar_t__ build_delete (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ build_modify_expr (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_vec_init (scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ build_x_compound_expr_from_list (scalar_t__,char*) ; 
 int /*<<< orphan*/  current_class_ref ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_eh_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  finish_expr_stmt (scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  sfk_complete_destructor ; 
 scalar_t__ void_type_node ; 
 scalar_t__ warn_ecpp ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
perform_member_init (tree member, tree init)
{
  tree decl;
  tree type = TREE_TYPE (member);
  bool explicit;

  explicit = (init != NULL_TREE);

  /* Effective C++ rule 12 requires that all data members be
     initialized.  */
  if (warn_ecpp && !explicit && TREE_CODE (type) != ARRAY_TYPE)
    warning (OPT_Weffc__, "%J%qD should be initialized in the member initialization "
	     "list", current_function_decl, member);

  if (init == void_type_node)
    init = NULL_TREE;

  /* Get an lvalue for the data member.  */
  decl = build_class_member_access_expr (current_class_ref, member,
					 /*access_path=*/NULL_TREE,
					 /*preserve_reference=*/true);
  if (decl == error_mark_node)
    return;

  /* Deal with this here, as we will get confused if we try to call the
     assignment op for an anonymous union.  This can happen in a
     synthesized copy constructor.  */
  if (ANON_AGGR_TYPE_P (type))
    {
      if (init)
	{
	  init = build2 (INIT_EXPR, type, decl, TREE_VALUE (init));
	  finish_expr_stmt (init);
	}
    }
  else if (TYPE_NEEDS_CONSTRUCTING (type))
    {
      if (explicit
	  && TREE_CODE (type) == ARRAY_TYPE
	  && init != NULL_TREE
	  && TREE_CHAIN (init) == NULL_TREE
	  && TREE_CODE (TREE_TYPE (TREE_VALUE (init))) == ARRAY_TYPE)
	{
	  /* Initialization of one array from another.  */
	  finish_expr_stmt (build_vec_init (decl, NULL_TREE, TREE_VALUE (init),
					    /*explicit_default_init_p=*/false,
					    /* from_array=*/1));
	}
      else
	finish_expr_stmt (build_aggr_init (decl, init, 0));
    }
  else
    {
      if (init == NULL_TREE)
	{
	  if (explicit)
	    {
	      init = build_default_init (type, /*nelts=*/NULL_TREE);
	      if (TREE_CODE (type) == REFERENCE_TYPE)
		warning (0, "%Jdefault-initialization of %q#D, "
			 "which has reference type",
			 current_function_decl, member);
	    }
	  /* member traversal: note it leaves init NULL */
	  else if (TREE_CODE (type) == REFERENCE_TYPE)
	    pedwarn ("%Juninitialized reference member %qD",
		     current_function_decl, member);
	  else if (CP_TYPE_CONST_P (type))
	    pedwarn ("%Juninitialized member %qD with %<const%> type %qT",
		     current_function_decl, member, type);
	}
      else if (TREE_CODE (init) == TREE_LIST)
	/* There was an explicit member initialization.  Do some work
	   in that case.  */
	init = build_x_compound_expr_from_list (init, "member initializer");

      if (init)
	finish_expr_stmt (build_modify_expr (decl, INIT_EXPR, init));
    }

  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type))
    {
      tree expr;

      expr = build_class_member_access_expr (current_class_ref, member,
					     /*access_path=*/NULL_TREE,
					     /*preserve_reference=*/false);
      expr = build_delete (type, expr, sfk_complete_destructor,
			   LOOKUP_NONVIRTUAL|LOOKUP_DESTRUCTOR, 0);

      if (expr != error_mark_node)
	finish_eh_cleanup (expr);
    }
}