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
struct mem_ref {struct mem_ref* next; } ;

/* Variables and functions */
 scalar_t__ should_issue_prefetch_p (struct mem_ref*) ; 

__attribute__((used)) static bool
anything_to_prefetch_p (struct mem_ref_group *groups)
{
  struct mem_ref *ref;

  for (; groups; groups = groups->next)
    for (ref = groups->refs; ref; ref = ref->next)
      if (should_issue_prefetch_p (ref))
	return true;

  return false;
}