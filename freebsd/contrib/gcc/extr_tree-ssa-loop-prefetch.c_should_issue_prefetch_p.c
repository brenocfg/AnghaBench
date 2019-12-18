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
struct mem_ref {scalar_t__ prefetch_before; } ;

/* Variables and functions */
 scalar_t__ PREFETCH_ALL ; 

__attribute__((used)) static bool
should_issue_prefetch_p (struct mem_ref *ref)
{
  /* For now do not issue prefetches for only first few of the
     iterations.  */
  if (ref->prefetch_before != PREFETCH_ALL)
    return false;

  return true;
}