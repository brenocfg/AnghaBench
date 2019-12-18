#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  inlinable; scalar_t__ disregard_inline_limits; } ;
struct TYPE_7__ {int /*<<< orphan*/  estimated_growth; scalar_t__ inlined_to; } ;
struct cgraph_node {struct cgraph_edge* callers; TYPE_2__ local; TYPE_1__ global; int /*<<< orphan*/  uid; } ;
struct cgraph_edge {char const* inline_failed; TYPE_3__* aux; struct cgraph_edge* next_caller; } ;
typedef  TYPE_3__* fibnode_t ;
typedef  int /*<<< orphan*/  fibheap_t ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_9__ {int key; struct cgraph_edge* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_default_inline_p (struct cgraph_node*,char const**) ; 
 int cgraph_edge_badness (struct cgraph_edge*) ; 
 int /*<<< orphan*/  fibheap_delete_node (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* fibheap_insert (int /*<<< orphan*/ ,int,struct cgraph_edge*) ; 
 scalar_t__ fibheap_replace_key (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
update_caller_keys (fibheap_t heap, struct cgraph_node *node,
		    bitmap updated_nodes)
{
  struct cgraph_edge *edge;
  const char *failed_reason;

  if (!node->local.inlinable || node->local.disregard_inline_limits
      || node->global.inlined_to)
    return;
  if (bitmap_bit_p (updated_nodes, node->uid))
    return;
  bitmap_set_bit (updated_nodes, node->uid);
  node->global.estimated_growth = INT_MIN;

  if (!node->local.inlinable)
    return;
  /* Prune out edges we won't inline into anymore.  */
  if (!cgraph_default_inline_p (node, &failed_reason))
    {
      for (edge = node->callers; edge; edge = edge->next_caller)
	if (edge->aux)
	  {
	    fibheap_delete_node (heap, edge->aux);
	    edge->aux = NULL;
	    if (edge->inline_failed)
	      edge->inline_failed = failed_reason;
	  }
      return;
    }

  for (edge = node->callers; edge; edge = edge->next_caller)
    if (edge->inline_failed)
      {
	int badness = cgraph_edge_badness (edge);
	if (edge->aux)
	  {
	    fibnode_t n = edge->aux;
	    gcc_assert (n->data == edge);
	    if (n->key == badness)
	      continue;

	    /* fibheap_replace_key only increase the keys.  */
	    if (fibheap_replace_key (heap, n, badness))
	      continue;
	    fibheap_delete_node (heap, edge->aux);
	  }
	edge->aux = fibheap_insert (heap, badness, edge);
      }
}