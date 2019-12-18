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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TARGET_CALLEE_INTERWORKING ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

int
is_called_in_ARM_mode (tree func)
{
  gcc_assert (TREE_CODE (func) == FUNCTION_DECL);

  /* Ignore the problem about functions whose address is taken.  */
  if (TARGET_CALLEE_INTERWORKING && TREE_PUBLIC (func))
    return TRUE;

#ifdef ARM_PE
  return lookup_attribute ("interfacearm", DECL_ATTRIBUTES (func)) != NULL_TREE;
#else
  return FALSE;
#endif
}