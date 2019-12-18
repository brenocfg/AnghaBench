#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inlined_to; int /*<<< orphan*/  insns; } ;
struct TYPE_3__ {scalar_t__ inlinable; int /*<<< orphan*/  self_insns; } ;
struct cgraph_node {TYPE_2__ global; struct cgraph_node* next; scalar_t__ callers; scalar_t__ reachable; scalar_t__ needed; TYPE_1__ local; scalar_t__ analyzed; int /*<<< orphan*/  decl; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 scalar_t__ cgraph_decide_inlining_incrementally (struct cgraph_node*,int) ; 
 int cgraph_n_nodes ; 
 struct cgraph_node* cgraph_nodes ; 
 int cgraph_postorder (struct cgraph_node**) ; 
 int /*<<< orphan*/  cgraph_remove_unreachable_nodes (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  estimate_num_insns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct cgraph_node** ggc_alloc (int) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 int /*<<< orphan*/  ggc_free (struct cgraph_node**) ; 
 int nnodes ; 
 struct cgraph_node** order ; 
 scalar_t__ sorrycount ; 

__attribute__((used)) static unsigned int
cgraph_early_inlining (void)
{
  struct cgraph_node *node;
  int i;

  if (sorrycount || errorcount)
    return 0;
#ifdef ENABLE_CHECKING
  for (node = cgraph_nodes; node; node = node->next)
    gcc_assert (!node->aux);
#endif

  order = ggc_alloc (sizeof (*order) * cgraph_n_nodes);
  nnodes = cgraph_postorder (order);
  for (i = nnodes - 1; i >= 0; i--)
    {
      node = order[i];
      if (node->analyzed && (node->needed || node->reachable))
        node->local.self_insns = node->global.insns
	  = estimate_num_insns (node->decl);
    }
  for (i = nnodes - 1; i >= 0; i--)
    {
      node = order[i];
      if (node->analyzed && node->local.inlinable
	  && (node->needed || node->reachable)
	  && node->callers)
	{
	  if (cgraph_decide_inlining_incrementally (node, true))
	    ggc_collect ();
	}
    }
  cgraph_remove_unreachable_nodes (true, dump_file);
#ifdef ENABLE_CHECKING
  for (node = cgraph_nodes; node; node = node->next)
    gcc_assert (!node->global.inlined_to);
#endif
  ggc_free (order);
  order = NULL;
  nnodes = 0;
  return 0;
}