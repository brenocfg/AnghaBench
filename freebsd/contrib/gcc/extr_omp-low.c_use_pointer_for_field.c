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

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ RESULT_DECL ; 
 scalar_t__ TREE_ADDRESSABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
use_pointer_for_field (tree decl, bool shared_p)
{
  if (AGGREGATE_TYPE_P (TREE_TYPE (decl)))
    return true;

  /* We can only use copy-in/copy-out semantics for shared variables
     when we know the value is not accessible from an outer scope.  */
  if (shared_p)
    {
      /* ??? Trivially accessible from anywhere.  But why would we even
	 be passing an address in this case?  Should we simply assert
	 this to be false, or should we have a cleanup pass that removes
	 these from the list of mappings?  */
      if (TREE_STATIC (decl) || DECL_EXTERNAL (decl))
	return true;

      /* For variables with DECL_HAS_VALUE_EXPR_P set, we cannot tell
	 without analyzing the expression whether or not its location
	 is accessible to anyone else.  In the case of nested parallel
	 regions it certainly may be.  */
      if (TREE_CODE (decl) != RESULT_DECL && DECL_HAS_VALUE_EXPR_P (decl))
	return true;

      /* Do not use copy-in/copy-out for variables that have their
	 address taken.  */
      if (TREE_ADDRESSABLE (decl))
	return true;
    }

  return false;
}