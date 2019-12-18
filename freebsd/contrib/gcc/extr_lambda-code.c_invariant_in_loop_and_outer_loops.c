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
struct loop {scalar_t__ depth; struct loop* outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  expr_invariant_in_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
invariant_in_loop_and_outer_loops (struct loop *loop, tree op)
{
  if (is_gimple_min_invariant (op))
    return true;
  if (loop->depth == 0)
    return true;
  if (!expr_invariant_in_loop_p (loop, op))
    return false;
  if (loop->outer 
      && !invariant_in_loop_and_outer_loops (loop->outer, op))
    return false;
  return true;
}