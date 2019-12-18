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
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  VEC_DELETE_EXPR ; 
 int /*<<< orphan*/  ansi_opname (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_fnfields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 
 scalar_t__ void_list_node ; 

__attribute__((used)) static bool
type_requires_array_cookie (tree type)
{
  tree fns;
  bool has_two_argument_delete_p = false;

  gcc_assert (CLASS_TYPE_P (type));

  /* If there's a non-trivial destructor, we need a cookie.  In order
     to iterate through the array calling the destructor for each
     element, we'll have to know how many elements there are.  */
  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type))
    return true;

  /* If the usual deallocation function is a two-argument whose second
     argument is of type `size_t', then we have to pass the size of
     the array to the deallocation function, so we will need to store
     a cookie.  */
  fns = lookup_fnfields (TYPE_BINFO (type),
			 ansi_opname (VEC_DELETE_EXPR),
			 /*protect=*/0);
  /* If there are no `operator []' members, or the lookup is
     ambiguous, then we don't need a cookie.  */
  if (!fns || fns == error_mark_node)
    return false;
  /* Loop through all of the functions.  */
  for (fns = BASELINK_FUNCTIONS (fns); fns; fns = OVL_NEXT (fns))
    {
      tree fn;
      tree second_parm;

      /* Select the current function.  */
      fn = OVL_CURRENT (fns);
      /* See if this function is a one-argument delete function.  If
	 it is, then it will be the usual deallocation function.  */
      second_parm = TREE_CHAIN (TYPE_ARG_TYPES (TREE_TYPE (fn)));
      if (second_parm == void_list_node)
	return false;
      /* Otherwise, if we have a two-argument function and the second
	 argument is `size_t', it will be the usual deallocation
	 function -- unless there is one-argument function, too.  */
      if (TREE_CHAIN (second_parm) == void_list_node
	  && same_type_p (TREE_VALUE (second_parm), sizetype))
	has_two_argument_delete_p = true;
    }

  return has_two_argument_delete_p;
}