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
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ get_first_fn (scalar_t__) ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 
 scalar_t__ push_using_decl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
validate_nonmember_using_decl (tree decl, tree scope, tree name)
{
  /* [namespace.udecl]
       A using-declaration for a class member shall be a
       member-declaration.  */
  if (TYPE_P (scope))
    {
      error ("%qT is not a namespace", scope);
      return NULL_TREE;
    }
  else if (scope == error_mark_node)
    return NULL_TREE;

  if (TREE_CODE (decl) == TEMPLATE_ID_EXPR)
    {
      /* 7.3.3/5
	   A using-declaration shall not name a template-id.  */
      error ("a using-declaration cannot specify a template-id.  "
	     "Try %<using %D%>", name);
      return NULL_TREE;
    }

  if (TREE_CODE (decl) == NAMESPACE_DECL)
    {
      error ("namespace %qD not allowed in using-declaration", decl);
      return NULL_TREE;
    }

  if (TREE_CODE (decl) == SCOPE_REF)
    {
      /* It's a nested name with template parameter dependent scope.
	 This can only be using-declaration for class member.  */
      error ("%qT is not a namespace", TREE_OPERAND (decl, 0));
      return NULL_TREE;
    }

  if (is_overloaded_fn (decl))
    decl = get_first_fn (decl);

  gcc_assert (DECL_P (decl));

  /* Make a USING_DECL.  */
  return push_using_decl (scope, name);
}