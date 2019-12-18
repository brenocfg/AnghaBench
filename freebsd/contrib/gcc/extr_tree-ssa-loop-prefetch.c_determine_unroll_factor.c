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
struct mem_ref_group {struct mem_ref* refs; struct mem_ref_group* next; } ;
struct mem_ref {unsigned int prefetch_mod; struct mem_ref* next; } ;
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARAM_MAX_UNROLLED_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNROLL_TIMES ; 
 unsigned int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 unsigned int SIMULTANEOUS_PREFETCHES ; 
 scalar_t__ should_issue_prefetch_p (struct mem_ref*) ; 
 int /*<<< orphan*/  should_unroll_loop_p (struct loop*,struct tree_niter_desc*,unsigned int) ; 

__attribute__((used)) static unsigned
determine_unroll_factor (struct loop *loop, struct mem_ref_group *refs,
			 unsigned ahead, unsigned ninsns,
			 struct tree_niter_desc *desc)
{
  unsigned upper_bound, size_factor, constraint_factor;
  unsigned factor, max_mod_constraint, ahead_factor;
  struct mem_ref_group *agp;
  struct mem_ref *ref;

  upper_bound = PARAM_VALUE (PARAM_MAX_UNROLL_TIMES);

  /* First check whether the loop is not too large to unroll.  */
  size_factor = PARAM_VALUE (PARAM_MAX_UNROLLED_INSNS) / ninsns;
  if (size_factor <= 1)
    return 1;

  if (size_factor < upper_bound)
    upper_bound = size_factor;

  max_mod_constraint = 1;
  for (agp = refs; agp; agp = agp->next)
    for (ref = agp->refs; ref; ref = ref->next)
      if (should_issue_prefetch_p (ref)
	  && ref->prefetch_mod > max_mod_constraint)
	max_mod_constraint = ref->prefetch_mod;

  /* Set constraint_factor as large as needed to be able to satisfy the
     largest modulo constraint.  */
  constraint_factor = max_mod_constraint;

  /* If ahead is too large in comparison with the number of available
     prefetches, unroll the loop as much as needed to be able to prefetch
     at least partially some of the references in the loop.  */
  ahead_factor = ((ahead + SIMULTANEOUS_PREFETCHES - 1)
		  / SIMULTANEOUS_PREFETCHES);

  /* Unroll as much as useful, but bound the code size growth.  */
  if (constraint_factor < ahead_factor)
    factor = ahead_factor;
  else
    factor = constraint_factor;
  if (factor > upper_bound)
    factor = upper_bound;

  if (!should_unroll_loop_p (loop, desc, factor))
    return 1;

  return factor;
}