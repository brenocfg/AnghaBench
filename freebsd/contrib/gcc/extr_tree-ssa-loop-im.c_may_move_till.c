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
struct loop {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_element_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_low_bound (int /*<<< orphan*/ ) ; 
 struct loop* outermost_invariant_loop (int /*<<< orphan*/ ,struct loop*) ; 
 struct loop* outermost_invariant_loop_expr (int /*<<< orphan*/ ,struct loop*) ; 

__attribute__((used)) static bool
may_move_till (tree ref, tree *index, void *data)
{
  struct loop *loop = data, *max_loop;

  /* If REF is an array reference, check also that the step and the lower
     bound is invariant in LOOP.  */
  if (TREE_CODE (ref) == ARRAY_REF)
    {
      tree step = array_ref_element_size (ref);
      tree lbound = array_ref_low_bound (ref);

      max_loop = outermost_invariant_loop_expr (step, loop);
      if (!max_loop)
	return false;

      max_loop = outermost_invariant_loop_expr (lbound, loop);
      if (!max_loop)
	return false;
    }

  max_loop = outermost_invariant_loop (*index, loop);
  if (!max_loop)
    return false;

  return true;
}