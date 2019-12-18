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
struct TYPE_4__ {int insns; struct cgraph_node* inlined_to; } ;
struct cgraph_node {scalar_t__ decl; int count; int needed; TYPE_2__ global; struct cgraph_node* next; TYPE_1__* callers; struct cgraph_edge* callees; } ;
struct cgraph_edge {int count; struct cgraph_node* callee; struct cgraph_node* caller; int /*<<< orphan*/  inline_failed; struct cgraph_edge* next_callee; } ;
typedef  int /*<<< orphan*/  fibheap_t ;
struct TYPE_3__ {struct cgraph_node* caller; } ;

/* Variables and functions */
 scalar_t__ DECL_DECLARED_INLINE_P (scalar_t__) ; 
 int /*<<< orphan*/  PARAM_MAX_INLINE_INSNS_RECURSIVE ; 
 int /*<<< orphan*/  PARAM_MAX_INLINE_INSNS_RECURSIVE_AUTO ; 
 int /*<<< orphan*/  PARAM_MAX_INLINE_RECURSIVE_DEPTH ; 
 int /*<<< orphan*/  PARAM_MAX_INLINE_RECURSIVE_DEPTH_AUTO ; 
 int /*<<< orphan*/  PARAM_MIN_INLINE_RECURSIVE_PROBABILITY ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_clone_inlined_nodes (struct cgraph_edge*,int,int) ; 
 struct cgraph_node* cgraph_clone_node (struct cgraph_node*,int,int,int) ; 
 int cgraph_estimate_size_after_inlining (int,struct cgraph_node*,struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_mark_inline_edge (struct cgraph_edge*,int) ; 
 int /*<<< orphan*/  cgraph_maybe_hot_edge_p (struct cgraph_edge*) ; 
 char* cgraph_node_name (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  cgraph_redirect_edge_callee (struct cgraph_edge*,struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_remove_node (struct cgraph_node*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fibheap_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ fibheap_empty (int /*<<< orphan*/ ) ; 
 struct cgraph_edge* fibheap_extract_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fibheap_new () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  lookup_recursive_calls (struct cgraph_node*,struct cgraph_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ max_count ; 

__attribute__((used)) static bool
cgraph_decide_recursive_inlining (struct cgraph_node *node)
{
  int limit = PARAM_VALUE (PARAM_MAX_INLINE_INSNS_RECURSIVE_AUTO);
  int max_depth = PARAM_VALUE (PARAM_MAX_INLINE_RECURSIVE_DEPTH_AUTO);
  int probability = PARAM_VALUE (PARAM_MIN_INLINE_RECURSIVE_PROBABILITY);
  fibheap_t heap;
  struct cgraph_edge *e;
  struct cgraph_node *master_clone, *next;
  int depth = 0;
  int n = 0;

  if (DECL_DECLARED_INLINE_P (node->decl))
    {
      limit = PARAM_VALUE (PARAM_MAX_INLINE_INSNS_RECURSIVE);
      max_depth = PARAM_VALUE (PARAM_MAX_INLINE_RECURSIVE_DEPTH);
    }

  /* Make sure that function is small enough to be considered for inlining.  */
  if (!max_depth
      || cgraph_estimate_size_after_inlining (1, node, node)  >= limit)
    return false;
  heap = fibheap_new ();
  lookup_recursive_calls (node, node, heap);
  if (fibheap_empty (heap))
    {
      fibheap_delete (heap);
      return false;
    }

  if (dump_file)
    fprintf (dump_file, 
	     "  Performing recursive inlining on %s\n",
	     cgraph_node_name (node));

  /* We need original clone to copy around.  */
  master_clone = cgraph_clone_node (node, node->count, 1, false);
  master_clone->needed = true;
  for (e = master_clone->callees; e; e = e->next_callee)
    if (!e->inline_failed)
      cgraph_clone_inlined_nodes (e, true, false);

  /* Do the inlining and update list of recursive call during process.  */
  while (!fibheap_empty (heap)
	 && (cgraph_estimate_size_after_inlining (1, node, master_clone)
	     <= limit))
    {
      struct cgraph_edge *curr = fibheap_extract_min (heap);
      struct cgraph_node *cnode;

      depth = 1;
      for (cnode = curr->caller;
	   cnode->global.inlined_to; cnode = cnode->callers->caller)
	if (node->decl == curr->callee->decl)
	  depth++;
      if (depth > max_depth)
	{
          if (dump_file)
	    fprintf (dump_file, 
		     "   maxmal depth reached\n");
	  continue;
	}

      if (max_count)
	{
          if (!cgraph_maybe_hot_edge_p (curr))
	    {
	      if (dump_file)
		fprintf (dump_file, "   Not inlining cold call\n");
	      continue;
	    }
          if (curr->count * 100 / node->count < probability)
	    {
	      if (dump_file)
		fprintf (dump_file, 
			 "   Probability of edge is too small\n");
	      continue;
	    }
	}

      if (dump_file)
	{
	  fprintf (dump_file, 
		   "   Inlining call of depth %i", depth);
	  if (node->count)
	    {
	      fprintf (dump_file, " called approx. %.2f times per call",
		       (double)curr->count / node->count);
	    }
	  fprintf (dump_file, "\n");
	}
      cgraph_redirect_edge_callee (curr, master_clone);
      cgraph_mark_inline_edge (curr, false);
      lookup_recursive_calls (node, curr->callee, heap);
      n++;
    }
  if (!fibheap_empty (heap) && dump_file)
    fprintf (dump_file, "    Recursive inlining growth limit met.\n");

  fibheap_delete (heap);
  if (dump_file)
    fprintf (dump_file, 
	     "\n   Inlined %i times, body grown from %i to %i insns\n", n,
	     master_clone->global.insns, node->global.insns);

  /* Remove master clone we used for inlining.  We rely that clones inlined
     into master clone gets queued just before master clone so we don't
     need recursion.  */
  for (node = cgraph_nodes; node != master_clone;
       node = next)
    {
      next = node->next;
      if (node->global.inlined_to == master_clone)
	cgraph_remove_node (node);
    }
  cgraph_remove_node (master_clone);
  /* FIXME: Recursive inlining actually reduces number of calls of the
     function.  At this place we should probably walk the function and
     inline clones and compensate the counts accordingly.  This probably
     doesn't matter much in practice.  */
  return n > 0;
}