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
 scalar_t__ CLASSTYPE_BEFRIENDING_CLASSES (scalar_t__) ; 
 scalar_t__ DECL_BEFRIENDING_CLASSES (scalar_t__) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_FUNCTION_TEMPLATE_P (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 scalar_t__ protected_accessible_p (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
friend_accessible_p (tree scope, tree decl, tree binfo)
{
  tree befriending_classes;
  tree t;

  if (!scope)
    return 0;

  if (TREE_CODE (scope) == FUNCTION_DECL
      || DECL_FUNCTION_TEMPLATE_P (scope))
    befriending_classes = DECL_BEFRIENDING_CLASSES (scope);
  else if (TYPE_P (scope))
    befriending_classes = CLASSTYPE_BEFRIENDING_CLASSES (scope);
  else
    return 0;

  for (t = befriending_classes; t; t = TREE_CHAIN (t))
    if (protected_accessible_p (decl, TREE_VALUE (t), binfo))
      return 1;

  /* Nested classes have the same access as their enclosing types, as
     per DR 45 (this is a change from the standard).  */
  if (TYPE_P (scope))
    for (t = TYPE_CONTEXT (scope); t && TYPE_P (t); t = TYPE_CONTEXT (t))
      if (protected_accessible_p (decl, t, binfo))
	return 1;

  if (TREE_CODE (scope) == FUNCTION_DECL
      || DECL_FUNCTION_TEMPLATE_P (scope))
    {
      /* Perhaps this SCOPE is a member of a class which is a
	 friend.  */
      if (DECL_CLASS_SCOPE_P (scope)
	  && friend_accessible_p (DECL_CONTEXT (scope), decl, binfo))
	return 1;

      /* Or an instantiation of something which is a friend.  */
      if (DECL_TEMPLATE_INFO (scope))
	{
	  int ret;
	  /* Increment processing_template_decl to make sure that
	     dependent_type_p works correctly.  */
	  ++processing_template_decl;
	  ret = friend_accessible_p (DECL_TI_TEMPLATE (scope), decl, binfo);
	  --processing_template_decl;
	  return ret;
	}
    }

  return 0;
}