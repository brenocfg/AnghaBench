#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inlinable; scalar_t__ redefined_extern_inline; } ;
struct cgraph_node {TYPE_1__ local; struct cgraph_edge* callers; } ;
struct cgraph_edge {int inline_failed; TYPE_3__* callee; struct cgraph_edge* next_caller; } ;
struct TYPE_5__ {int /*<<< orphan*/  inlined_to; } ;
struct TYPE_6__ {TYPE_2__ global; } ;

/* Variables and functions */
 void* N_ (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
initialize_inline_failed (struct cgraph_node *node)
{
  struct cgraph_edge *e;

  for (e = node->callers; e; e = e->next_caller)
    {
      gcc_assert (!e->callee->global.inlined_to);
      gcc_assert (e->inline_failed);
      if (node->local.redefined_extern_inline)
	e->inline_failed = N_("redefined extern inline functions are not "
			   "considered for inlining");
      else if (!node->local.inlinable)
	e->inline_failed = N_("function not inlinable");
      else
	e->inline_failed = N_("function not considered for inlining");
    }
}