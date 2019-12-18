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
typedef  int /*<<< orphan*/  linkage_kind ;

/* Variables and functions */
 scalar_t__ CONST_DECL ; 
 scalar_t__ DECL_COMDAT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_THIS_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ decl_function_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lk_external ; 
 int /*<<< orphan*/  lk_internal ; 
 int /*<<< orphan*/  lk_none ; 

linkage_kind
decl_linkage (tree decl)
{
  /* This function doesn't attempt to calculate the linkage from first
     principles as given in [basic.link].  Instead, it makes use of
     the fact that we have already set TREE_PUBLIC appropriately, and
     then handles a few special cases.  Ideally, we would calculate
     linkage first, and then transform that into a concrete
     implementation.  */

  /* Things that don't have names have no linkage.  */
  if (!DECL_NAME (decl))
    return lk_none;

  /* Things that are TREE_PUBLIC have external linkage.  */
  if (TREE_PUBLIC (decl))
    return lk_external;

  if (TREE_CODE (decl) == NAMESPACE_DECL)
    return lk_external;

  /* Linkage of a CONST_DECL depends on the linkage of the enumeration
     type.  */
  if (TREE_CODE (decl) == CONST_DECL)
    return decl_linkage (TYPE_NAME (TREE_TYPE (decl)));

  /* Some things that are not TREE_PUBLIC have external linkage, too.
     For example, on targets that don't have weak symbols, we make all
     template instantiations have internal linkage (in the object
     file), but the symbols should still be treated as having external
     linkage from the point of view of the language.  */
  if (TREE_CODE (decl) != TYPE_DECL && DECL_LANG_SPECIFIC (decl)
      && DECL_COMDAT (decl))
    return lk_external;

  /* Things in local scope do not have linkage, if they don't have
     TREE_PUBLIC set.  */
  if (decl_function_context (decl))
    return lk_none;

  /* Members of the anonymous namespace also have TREE_PUBLIC unset, but
     are considered to have external linkage for language purposes.  DECLs
     really meant to have internal linkage have DECL_THIS_STATIC set.  */
  if (TREE_CODE (decl) == TYPE_DECL
      || ((TREE_CODE (decl) == VAR_DECL || TREE_CODE (decl) == FUNCTION_DECL)
	  && !DECL_THIS_STATIC (decl)))
    return lk_external;

  /* Everything else has internal linkage.  */
  return lk_internal;
}