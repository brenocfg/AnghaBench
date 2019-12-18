#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mem_ref {int prefetch_before; int prefetch_mod; TYPE_1__* group; } ;
struct TYPE_2__ {int step; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ HAVE_BACKWARD_PREFETCH ; 
 scalar_t__ HAVE_FORWARD_PREFETCH ; 
 int PREFETCH_BLOCK ; 

__attribute__((used)) static void
prune_ref_by_self_reuse (struct mem_ref *ref)
{
  HOST_WIDE_INT step = ref->group->step;
  bool backward = step < 0;

  if (step == 0)
    {
      /* Prefetch references to invariant address just once.  */
      ref->prefetch_before = 1;
      return;
    }

  if (backward)
    step = -step;

  if (step > PREFETCH_BLOCK)
    return;

  if ((backward && HAVE_BACKWARD_PREFETCH)
      || (!backward && HAVE_FORWARD_PREFETCH))
    {
      ref->prefetch_before = 1;
      return;
    }

  ref->prefetch_mod = PREFETCH_BLOCK / step;
}