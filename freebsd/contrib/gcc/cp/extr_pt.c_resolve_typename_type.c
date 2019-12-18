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
 scalar_t__ CLASSTYPE_PRIMARY_TEMPLATE_TYPE (scalar_t__) ; 
 scalar_t__ DECL_CLASS_TEMPLATE_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPENAME_TYPE ; 
 scalar_t__ TYPENAME_TYPE_FULLNAME (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_IDENTIFIER (scalar_t__) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,int) ; 
 int cp_type_quals (scalar_t__) ; 
 int /*<<< orphan*/  currently_open_class (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_member (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lookup_template_class (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pop_scope (scalar_t__) ; 
 scalar_t__ push_scope (scalar_t__) ; 
 int tf_error ; 
 int tf_user ; 

tree
resolve_typename_type (tree type, bool only_current_p)
{
  tree scope;
  tree name;
  tree decl;
  int quals;
  tree pushed_scope;

  gcc_assert (TREE_CODE (type) == TYPENAME_TYPE);

  scope = TYPE_CONTEXT (type);
  name = TYPE_IDENTIFIER (type);

  /* If the SCOPE is itself a TYPENAME_TYPE, then we need to resolve
     it first before we can figure out what NAME refers to.  */
  if (TREE_CODE (scope) == TYPENAME_TYPE)
    scope = resolve_typename_type (scope, only_current_p);
  /* If we don't know what SCOPE refers to, then we cannot resolve the
     TYPENAME_TYPE.  */
  if (scope == error_mark_node || TREE_CODE (scope) == TYPENAME_TYPE)
    return error_mark_node;
  /* If the SCOPE is a template type parameter, we have no way of
     resolving the name.  */
  if (TREE_CODE (scope) == TEMPLATE_TYPE_PARM)
    return type;
  /* If the SCOPE is not the current instantiation, there's no reason
     to look inside it.  */
  if (only_current_p && !currently_open_class (scope))
    return error_mark_node;
  /* If SCOPE is a partial instantiation, it will not have a valid
     TYPE_FIELDS list, so use the original template.  */
  scope = CLASSTYPE_PRIMARY_TEMPLATE_TYPE (scope);
  /* Enter the SCOPE so that name lookup will be resolved as if we
     were in the class definition.  In particular, SCOPE will no
     longer be considered a dependent type.  */
  pushed_scope = push_scope (scope);
  /* Look up the declaration.  */
  decl = lookup_member (scope, name, /*protect=*/0, /*want_type=*/true);
  /* Obtain the set of qualifiers applied to the TYPE.  */
  quals = cp_type_quals (type);
  /* For a TYPENAME_TYPE like "typename X::template Y<T>", we want to
     find a TEMPLATE_DECL.  Otherwise, we want to find a TYPE_DECL.  */
  if (!decl)
    type = error_mark_node;
  else if (TREE_CODE (TYPENAME_TYPE_FULLNAME (type)) == IDENTIFIER_NODE
	   && TREE_CODE (decl) == TYPE_DECL)
    type = TREE_TYPE (decl);
  else if (TREE_CODE (TYPENAME_TYPE_FULLNAME (type)) == TEMPLATE_ID_EXPR
	   && DECL_CLASS_TEMPLATE_P (decl))
    {
      tree tmpl;
      tree args;
      /* Obtain the template and the arguments.  */
      tmpl = TREE_OPERAND (TYPENAME_TYPE_FULLNAME (type), 0);
      args = TREE_OPERAND (TYPENAME_TYPE_FULLNAME (type), 1);
      /* Instantiate the template.  */
      type = lookup_template_class (tmpl, args, NULL_TREE, NULL_TREE,
				    /*entering_scope=*/0, tf_error | tf_user);
    }
  else
    type = error_mark_node;
  /* Qualify the resulting type.  */
  if (type != error_mark_node && quals)
    type = cp_build_qualified_type (type, quals);
  /* Leave the SCOPE.  */
  if (pushed_scope)
    pop_scope (pushed_scope);

  return type;
}