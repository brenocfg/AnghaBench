#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_11__ {scalar_t__ nodes; TYPE_1__* min; } ;
struct TYPE_10__ {struct TYPE_10__* right; int /*<<< orphan*/ * parent; struct TYPE_10__* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  fibheap_consolidate (TYPE_2__*) ; 
 int /*<<< orphan*/  fibheap_ins_root (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fibheap_rem_root (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static fibnode_t
fibheap_extr_min_node (fibheap_t heap)
{
  fibnode_t ret = heap->min;
  fibnode_t x, y, orig;

  /* Attach the child list of the minimum node to the root list of the heap.
     If there is no child list, we don't do squat.  */
  for (x = ret->child, orig = NULL; x != orig && x != NULL; x = y)
    {
      if (orig == NULL)
	orig = x;
      y = x->right;
      x->parent = NULL;
      fibheap_ins_root (heap, x);
    }

  /* Remove the old root.  */
  fibheap_rem_root (heap, ret);
  heap->nodes--;

  /* If we are left with no nodes, then the min is NULL.  */
  if (heap->nodes == 0)
    heap->min = NULL;
  else
    {
      /* Otherwise, consolidate to find new minimum, as well as do the reorg
         work that needs to be done.  */
      heap->min = ret->right;
      fibheap_consolidate (heap);
    }

  return ret;
}