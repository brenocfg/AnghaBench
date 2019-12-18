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
typedef  int tsubst_flags_t ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  BASELINK_P (scalar_t__) ; 
 scalar_t__ BIT_NOT_EXPR ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_RESULT (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OFFSET_REF ; 
 int /*<<< orphan*/  QUALIFIED_NAME_IS_TEMPLATE (scalar_t__) ; 
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ adjust_result_of_qualified_name_lookup (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_qualified_name (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_accessibility_of_qualified_id (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ convert_from_reference (scalar_t__) ; 
 int /*<<< orphan*/  current_class_type ; 
 scalar_t__ dependent_type_p (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ finish_qualified_id_expr (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  inform (char*,scalar_t__) ; 
 scalar_t__ lookup_qualified_name (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lookup_template_function (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mark_used (scalar_t__) ; 
 int /*<<< orphan*/  qualified_name_lookup_error (scalar_t__,scalar_t__,scalar_t__) ; 
 int tf_error ; 
 scalar_t__ tsubst (scalar_t__,scalar_t__,int,scalar_t__) ; 
 scalar_t__ tsubst_copy (scalar_t__,scalar_t__,int,scalar_t__) ; 
 scalar_t__ tsubst_template_args (scalar_t__,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static tree
tsubst_qualified_id (tree qualified_id, tree args,
		     tsubst_flags_t complain, tree in_decl,
		     bool done, bool address_p)
{
  tree expr;
  tree scope;
  tree name;
  bool is_template;
  tree template_args;

  gcc_assert (TREE_CODE (qualified_id) == SCOPE_REF);

  /* Figure out what name to look up.  */
  name = TREE_OPERAND (qualified_id, 1);
  if (TREE_CODE (name) == TEMPLATE_ID_EXPR)
    {
      is_template = true;
      template_args = TREE_OPERAND (name, 1);
      if (template_args)
	template_args = tsubst_template_args (template_args, args,
					      complain, in_decl);
      name = TREE_OPERAND (name, 0);
    }
  else
    {
      is_template = false;
      template_args = NULL_TREE;
    }

  /* Substitute into the qualifying scope.  When there are no ARGS, we
     are just trying to simplify a non-dependent expression.  In that
     case the qualifying scope may be dependent, and, in any case,
     substituting will not help.  */
  scope = TREE_OPERAND (qualified_id, 0);
  if (args)
    {
      scope = tsubst (scope, args, complain, in_decl);
      expr = tsubst_copy (name, args, complain, in_decl);
    }
  else
    expr = name;

  if (dependent_type_p (scope))
    return build_qualified_name (/*type=*/NULL_TREE,
				 scope, expr,
				 QUALIFIED_NAME_IS_TEMPLATE (qualified_id));

  if (!BASELINK_P (name) && !DECL_P (expr))
    {
      if (TREE_CODE (expr) == BIT_NOT_EXPR)
	/* If this were actually a destructor call, it would have been
	   parsed as such by the parser.  */
	expr = error_mark_node;
      else
	expr = lookup_qualified_name (scope, expr, /*is_type_p=*/0, false);
      if (TREE_CODE (TREE_CODE (expr) == TEMPLATE_DECL
		     ? DECL_TEMPLATE_RESULT (expr) : expr) == TYPE_DECL)
	{
	  if (complain & tf_error)
	    {
	      error ("dependent-name %qE is parsed as a non-type, but "
		     "instantiation yields a type", qualified_id);
	      inform ("say %<typename %E%> if a type is meant", qualified_id);
	    }
	  return error_mark_node;
	}
    }

  if (DECL_P (expr))
    {
      check_accessibility_of_qualified_id (expr, /*object_type=*/NULL_TREE,
					   scope);
      /* Remember that there was a reference to this entity.  */
      mark_used (expr);
    }

  if (expr == error_mark_node || TREE_CODE (expr) == TREE_LIST)
    {
      if (complain & tf_error)
	qualified_name_lookup_error (scope,
				     TREE_OPERAND (qualified_id, 1),
				     expr);
      return error_mark_node;
    }

  if (is_template)
    expr = lookup_template_function (expr, template_args);

  if (expr == error_mark_node && complain & tf_error)
    qualified_name_lookup_error (scope, TREE_OPERAND (qualified_id, 1),
				 expr);
  else if (TYPE_P (scope))
    {
      expr = (adjust_result_of_qualified_name_lookup
	      (expr, scope, current_class_type));
      expr = (finish_qualified_id_expr
	      (scope, expr, done, address_p,
	       QUALIFIED_NAME_IS_TEMPLATE (qualified_id),
	       /*template_arg_p=*/false));
    }

  /* Expressions do not generally have reference type.  */
  if (TREE_CODE (expr) != SCOPE_REF
      /* However, if we're about to form a pointer-to-member, we just
	 want the referenced member referenced.  */
      && TREE_CODE (expr) != OFFSET_REF)
    expr = convert_from_reference (expr);

  return expr;
}