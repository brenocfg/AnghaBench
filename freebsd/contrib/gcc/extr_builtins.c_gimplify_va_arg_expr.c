#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
struct TYPE_4__ {scalar_t__ (* type_promotes_to ) (scalar_t__) ;} ;
struct TYPE_6__ {TYPE_1__ types; } ;
struct TYPE_5__ {scalar_t__ (* gimplify_va_arg_expr ) (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 size_t BUILT_IN_TRAP ; 
 int GS_ALL_DONE ; 
 int GS_ERROR ; 
 int GS_OK ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  append_to_statement_list (scalar_t__,scalar_t__*) ; 
 scalar_t__ build_fold_addr_expr_with_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ dummy_object (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  fb_lvalue ; 
 int /*<<< orphan*/  fb_rvalue ; 
 int /*<<< orphan*/  gimplify_expr (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 int /*<<< orphan*/  inform (char*) ; 
 int /*<<< orphan*/  is_gimple_min_lval ; 
 int /*<<< orphan*/  is_gimple_val ; 
 TYPE_3__ lang_hooks ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 TYPE_2__ targetm ; 
 scalar_t__ va_list_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

enum gimplify_status
gimplify_va_arg_expr (tree *expr_p, tree *pre_p, tree *post_p)
{
  tree promoted_type, want_va_type, have_va_type;
  tree valist = TREE_OPERAND (*expr_p, 0);
  tree type = TREE_TYPE (*expr_p);
  tree t;

  /* Verify that valist is of the proper type.  */
  want_va_type = va_list_type_node;
  have_va_type = TREE_TYPE (valist);

  if (have_va_type == error_mark_node)
    return GS_ERROR;

  if (TREE_CODE (want_va_type) == ARRAY_TYPE)
    {
      /* If va_list is an array type, the argument may have decayed
	 to a pointer type, e.g. by being passed to another function.
	 In that case, unwrap both types so that we can compare the
	 underlying records.  */
      if (TREE_CODE (have_va_type) == ARRAY_TYPE
	  || POINTER_TYPE_P (have_va_type))
	{
	  want_va_type = TREE_TYPE (want_va_type);
	  have_va_type = TREE_TYPE (have_va_type);
	}
    }

  if (TYPE_MAIN_VARIANT (want_va_type) != TYPE_MAIN_VARIANT (have_va_type))
    {
      error ("first argument to %<va_arg%> not of type %<va_list%>");
      return GS_ERROR;
    }

  /* Generate a diagnostic for requesting data of a type that cannot
     be passed through `...' due to type promotion at the call site.  */
  else if ((promoted_type = lang_hooks.types.type_promotes_to (type))
	   != type)
    {
      static bool gave_help;

      /* Unfortunately, this is merely undefined, rather than a constraint
	 violation, so we cannot make this an error.  If this call is never
	 executed, the program is still strictly conforming.  */
      warning (0, "%qT is promoted to %qT when passed through %<...%>",
	       type, promoted_type);
      if (! gave_help)
	{
	  gave_help = true;
	  warning (0, "(so you should pass %qT not %qT to %<va_arg%>)",
		   promoted_type, type);
	}

      /* We can, however, treat "undefined" any way we please.
	 Call abort to encourage the user to fix the program.  */
      inform ("if this code is reached, the program will abort");
      t = build_function_call_expr (implicit_built_in_decls[BUILT_IN_TRAP],
				    NULL);
      append_to_statement_list (t, pre_p);

      /* This is dead code, but go ahead and finish so that the
	 mode of the result comes out right.  */
      *expr_p = dummy_object (type);
      return GS_ALL_DONE;
    }
  else
    {
      /* Make it easier for the backends by protecting the valist argument
	 from multiple evaluations.  */
      if (TREE_CODE (va_list_type_node) == ARRAY_TYPE)
	{
	  /* For this case, the backends will be expecting a pointer to
	     TREE_TYPE (va_list_type_node), but it's possible we've
	     actually been given an array (an actual va_list_type_node).
	     So fix it.  */
	  if (TREE_CODE (TREE_TYPE (valist)) == ARRAY_TYPE)
	    {
	      tree p1 = build_pointer_type (TREE_TYPE (va_list_type_node));
	      valist = build_fold_addr_expr_with_type (valist, p1);
	    }
	  gimplify_expr (&valist, pre_p, post_p, is_gimple_val, fb_rvalue);
	}
      else
	gimplify_expr (&valist, pre_p, post_p, is_gimple_min_lval, fb_lvalue);

      if (!targetm.gimplify_va_arg_expr)
	/* FIXME:Once most targets are converted we should merely
	   assert this is non-null.  */
	return GS_ALL_DONE;

      *expr_p = targetm.gimplify_va_arg_expr (valist, type, pre_p, post_p);
      return GS_OK;
    }
}