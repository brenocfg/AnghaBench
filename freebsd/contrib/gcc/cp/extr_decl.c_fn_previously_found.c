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
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_EXTERN_C_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CHAIN (scalar_t__) ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ compparms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decls_match (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static bool
fn_previously_found (tree decl, tree olddecl)
{
  int types_match;

  if (olddecl == 0)
    return false;

  if (TREE_CODE (olddecl) == OVERLOAD)
    {
      if (OVL_CHAIN (olddecl) == NULL_TREE)
	olddecl = OVL_CURRENT (olddecl);
      else
	{
	  tree match;
	  for (match = olddecl; match; match = OVL_NEXT (match))
	    {
	      if (fn_previously_found (decl, OVL_CURRENT (match)))
		return true;
	    }
	  return false;
	}
    }	  

  /* Don't warn about previously erroneous things that have the same
     name.  */
  if (TREE_TYPE (olddecl) == error_mark_node)
    return true;

  /* Internally defined things still need a prototype to escape the
     warning.  */
  if (DECL_ARTIFICIAL (olddecl))
    return false;

  if (TREE_CODE (olddecl) != FUNCTION_DECL)
    return false;

  /* These will match or error, don't also spew prototype warnings.  */
  if (DECL_EXTERN_C_P (olddecl)
      && DECL_EXTERN_C_P (decl))
    return true;

  /* These will match or error, don't also spew prototype warnings.  */
  if (compparms (TYPE_ARG_TYPES (TREE_TYPE (decl)),
		 TYPE_ARG_TYPES (TREE_TYPE (olddecl))))
    return true;

  types_match = decls_match (decl, olddecl);
    
  if (types_match)
    return true;

  return false;
}