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
struct mem_ref_group {struct mem_ref* refs; struct mem_ref_group* next; } ;
struct mem_ref {int issue_prefetch_p; unsigned int prefetch_mod; struct mem_ref* next; } ;

/* Variables and functions */
 unsigned int SIMULTANEOUS_PREFETCHES ; 
 int TDF_DETAILS ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned int) ; 
 int /*<<< orphan*/  should_issue_prefetch_p (struct mem_ref*) ; 

__attribute__((used)) static bool
schedule_prefetches (struct mem_ref_group *groups, unsigned unroll_factor,
		     unsigned ahead)
{
  unsigned max_prefetches, n_prefetches;
  struct mem_ref *ref;
  bool any = false;

  max_prefetches = (SIMULTANEOUS_PREFETCHES * unroll_factor) / ahead;
  if (max_prefetches > (unsigned) SIMULTANEOUS_PREFETCHES)
    max_prefetches = SIMULTANEOUS_PREFETCHES;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Max prefetches to issue: %d.\n", max_prefetches);

  if (!max_prefetches)
    return false;

  /* For now we just take memory references one by one and issue
     prefetches for as many as possible.  The groups are sorted
     starting with the largest step, since the references with
     large step are more likely to cause many cache misses.  */

  for (; groups; groups = groups->next)
    for (ref = groups->refs; ref; ref = ref->next)
      {
	if (!should_issue_prefetch_p (ref))
	  continue;

	ref->issue_prefetch_p = true;

	/* If prefetch_mod is less then unroll_factor, we need to insert
	   several prefetches for the reference.  */
	n_prefetches = ((unroll_factor + ref->prefetch_mod - 1)
			/ ref->prefetch_mod);
	if (max_prefetches <= n_prefetches)
	  return true;

	max_prefetches -= n_prefetches;
	any = true;
      }

  return any;
}