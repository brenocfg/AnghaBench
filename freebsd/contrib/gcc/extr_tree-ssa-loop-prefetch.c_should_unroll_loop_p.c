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
struct tree_niter_desc {int dummy; } ;
struct loop {int num_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_unroll_loop_p (struct loop*,unsigned int,struct tree_niter_desc*) ; 

__attribute__((used)) static bool
should_unroll_loop_p (struct loop *loop, struct tree_niter_desc *desc,
		      unsigned factor)
{
  if (!can_unroll_loop_p (loop, factor, desc))
    return false;

  /* We only consider loops without control flow for unrolling.  This is not
     a hard restriction -- tree_unroll_loop works with arbitrary loops
     as well; but the unrolling/prefetching is usually more profitable for
     loops consisting of a single basic block, and we want to limit the
     code growth.  */
  if (loop->num_nodes > 2)
    return false;

  return true;
}