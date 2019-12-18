#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* fibnode_t ;
typedef  TYPE_2__* fibheap_t ;
struct TYPE_9__ {int /*<<< orphan*/  min; scalar_t__ nodes; TYPE_1__* root; } ;
struct TYPE_8__ {struct TYPE_8__* left; struct TYPE_8__* right; } ;

/* Variables and functions */
 scalar_t__ fibheap_compare (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

fibheap_t
fibheap_union (fibheap_t heapa, fibheap_t heapb)
{
  fibnode_t a_root, b_root, temp;

  /* If one of the heaps is empty, the union is just the other heap.  */
  if ((a_root = heapa->root) == NULL)
    {
      free (heapa);
      return heapb;
    }
  if ((b_root = heapb->root) == NULL)
    {
      free (heapb);
      return heapa;
    }

  /* Merge them to the next nodes on the opposite chain.  */
  a_root->left->right = b_root;
  b_root->left->right = a_root;
  temp = a_root->left;
  a_root->left = b_root->left;
  b_root->left = temp;
  heapa->nodes += heapb->nodes;

  /* And set the new minimum, if it's changed.  */
  if (fibheap_compare (heapa, heapb->min, heapa->min) < 0)
    heapa->min = heapb->min;

  free (heapb);
  return heapa;
}