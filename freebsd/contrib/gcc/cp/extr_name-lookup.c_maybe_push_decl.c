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
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_SPECIALIZATION (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ UNKNOWN_TYPE ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  namespace_bindings_p () ; 
 scalar_t__ pushdecl (scalar_t__) ; 

tree
maybe_push_decl (tree decl)
{
  tree type = TREE_TYPE (decl);

  /* Add this decl to the current binding level, but not if it comes
     from another scope, e.g. a static member variable.  TEM may equal
     DECL or it may be a previous decl of the same name.  */
  if (decl == error_mark_node
      || (TREE_CODE (decl) != PARM_DECL
	  && DECL_CONTEXT (decl) != NULL_TREE
	  /* Definitions of namespace members outside their namespace are
	     possible.  */
	  && TREE_CODE (DECL_CONTEXT (decl)) != NAMESPACE_DECL)
      || (TREE_CODE (decl) == TEMPLATE_DECL && !namespace_bindings_p ())
      || TREE_CODE (type) == UNKNOWN_TYPE
      /* The declaration of a template specialization does not affect
	 the functions available for overload resolution, so we do not
	 call pushdecl.  */
      || (TREE_CODE (decl) == FUNCTION_DECL
	  && DECL_TEMPLATE_SPECIALIZATION (decl)))
    return decl;
  else
    return pushdecl (decl);
}